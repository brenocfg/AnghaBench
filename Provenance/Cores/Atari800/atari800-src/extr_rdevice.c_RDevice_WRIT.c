#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  CPU_ClrN ; 
 int /*<<< orphan*/  CPU_SetN ; 
 int CPU_regA ; 
 int CPU_regY ; 
 int /*<<< orphan*/  DBG_APRINT (char*) ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 scalar_t__ RDevice_serial_enabled ; 
 int atoi (char*) ; 
 int bufend ; 
 unsigned char* bufout ; 
 char* command_buf ; 
 size_t command_end ; 
 scalar_t__ connected ; 
 int dc_write_serial (unsigned char) ; 
 scalar_t__ linefeeds ; 
 int /*<<< orphan*/  open_connection (char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  rdev_fd ; 
 int /*<<< orphan*/  strcat (unsigned char*,char*) ; 
 char* strchr (char*,char) ; 
 char* strrchr (char*,char) ; 
 int trans_cr ; 
 scalar_t__ translation ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

void RDevice_WRIT(void)
{
  unsigned char out_char;
#ifdef R_NETWORK
  int port;
#endif

  CPU_regY = 1;
  CPU_ClrN;

  /*bufend = Peek(747);*/

  /* Translation mode */
  if(translation)
  {
    if(CPU_regA == 0x9b)
    {
      out_char = 0x0d;
      if(linefeeds)
      {
        if((RDevice_serial_enabled == 0) && (connected == 0))
        { /* local echo */
          bufend++;
          bufout[bufend-1] = out_char;
          bufout[bufend] = 0;

          command_end = 0;
          command_buf[command_end] = 0;
          strcat(bufout, "OK\r\n");
          bufend += 4;

        }
        else
        {
#ifndef DREAMCAST
          write(rdev_fd, (char *)&out_char, 1); /* Write return */
#else
          dc_write_serial(out_char);
#endif
        }
        out_char = 0x0a;  /*set char for line feed to be output later....*/
      }
    }
  }
  else
  {
    out_char = CPU_regA;
  }

  /* Translate the CR to a LF for telnet, ftp, etc */
  if(connected && trans_cr && (out_char == 0x0d))
  {
    out_char = 0x0a;
  }

  /*if((RDevice_serial_enabled == 0) && (out_char == 255))*/
  /*{*/
  /*  DBG_APRINT("R: Writing IAC..."); */
  /*  retval = write(rdev_fd, &out_char, 1);*/ /* IAC escape sequence */ 
  /*}*/
  /*if(retval == -1)*/

#ifdef R_NETWORK
  if((RDevice_serial_enabled == 0) && (connected == 0))
  { /* Local echo - only do if in socket mode */
    bufend++;
    bufout[bufend-1] = out_char;
    bufout[bufend] = 0;

    /* Grab Command */
    if((out_char == 0x9b) || (out_char == 0x0d))
    { /*process command with a return/enter*/
      command_end = 0;

      /*Make out going connection command 'ATDI'*/
      if((command_buf[0] == 'A') && (command_buf[1] == 'T') && (command_buf[2] == 'D') && (command_buf[3] == 'I'))
      {
        /*DBG_APRINT(command_buf);*/
        if(strchr(command_buf, ' ') != NULL)
        {
          if(strrchr(command_buf, ' ') != strchr(command_buf, ' '))
          {
            port = atoi((char *)(strrchr(command_buf, ' ')+1));
            * strrchr(command_buf, ' ') = '\0'; /*zero last space in line*/
          }
          else
          {
            port = 23;
          }
          open_connection((char *)(strchr(command_buf, ' ')+1), port); /*send string after first space in line*/
        }
        command_buf[command_end] = 0;
        strcat(bufout, "OK\r\n");
        bufend += 4;
      /*Change translation command 'ATDL'*/
      }
      else if((command_buf[0] == 'A') && (command_buf[1] == 'T') && (command_buf[2] == 'D') && (command_buf[3] == 'L'))
      {
        trans_cr = (trans_cr + 1) % 2;

        command_buf[command_end] = 0;
        strcat(bufout, "OK\r\n");
        bufend += 4;
      }
    }
    else
    {
      if(((out_char == 0x7f) || (out_char == 0x08)) && (command_end > 0))
      {
        command_end--; /* backspace */
        command_buf[command_end] = 0;
      }
      else
      {
        command_buf[command_end] = out_char;
        command_buf[command_end+1] = 0;
        command_end = (command_end + 1) % 256;
      }
    }
  }
  else
#endif /* R_NETWORK */
#ifndef DREAMCAST
    if((connected) && (write(rdev_fd, (char *)&out_char, 1) < 1))
    { /* returns -1 if disconnected or 0 if could not send */
      perror("write");
      DBG_APRINT("R*: ERROR on write.");
      CPU_SetN;
      CPU_regY = 135;
      /*bufend = 13;*/ /* To catch NO CARRIER message */
    }
#else
  if (connected)
  {
    if (dc_write_serial(out_char) != 1)
    {
      Log_print("R*: ERROR on write.");
      CPU_SetN;
      CPU_regY = 135;
    }
  }
#endif

  CPU_regA = 1;
}