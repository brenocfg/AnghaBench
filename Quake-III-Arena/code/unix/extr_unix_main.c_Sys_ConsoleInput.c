#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_10__ {size_t cursor; char* buffer; } ;
typedef  TYPE_1__ field_t ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_12__ {int /*<<< orphan*/  value; } ;
struct TYPE_11__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_DPrintf (char*,char,char) ; 
 int /*<<< orphan*/  FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Field_Clear (TYPE_1__*) ; 
 int /*<<< orphan*/  Field_CompleteCommand (TYPE_1__*) ; 
 int /*<<< orphan*/  Hist_Add (TYPE_1__*) ; 
 TYPE_1__* Hist_Next () ; 
 TYPE_1__* Hist_Prev () ; 
 TYPE_4__* com_dedicated ; 
 scalar_t__ qfalse ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ stdin_active ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  tty_Back () ; 
 int /*<<< orphan*/  tty_FlushIn () ; 
 int /*<<< orphan*/  tty_Hide () ; 
 int /*<<< orphan*/  tty_Show () ; 
 TYPE_1__ tty_con ; 
 char tty_erase ; 
 TYPE_2__* ttycon ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

char *Sys_ConsoleInput(void)
{
  // we use this when sending back commands
  static char text[256];
  int i;
  int avail;
  char key;
  field_t *history;

  if (ttycon && ttycon->value)
  {
    avail = read(0, &key, 1);
    if (avail != -1)
    {
      // we have something
      // backspace?
      // NOTE TTimo testing a lot of values .. seems it's the only way to get it to work everywhere
      if ((key == tty_erase) || (key == 127) || (key == 8))
      {
        if (tty_con.cursor > 0)
        {
          tty_con.cursor--;
          tty_con.buffer[tty_con.cursor] = '\0';
          tty_Back();
        }
        return NULL;
      }
      // check if this is a control char
      if ((key) && (key) < ' ')
      {
        if (key == '\n')
        {
          // push it in history
          Hist_Add(&tty_con);
          strcpy(text, tty_con.buffer);
          Field_Clear(&tty_con);
          key = '\n';
          write(1, &key, 1);
          return text;
        }
        if (key == '\t')
        {
          tty_Hide();
          Field_CompleteCommand( &tty_con );
          // Field_CompleteCommand does weird things to the string, do a cleanup
          //   it adds a '\' at the beginning of the string
          //   cursor doesn't reflect actual length of the string that's sent back
          tty_con.cursor = strlen(tty_con.buffer);
          if (tty_con.cursor>0)
          {
            if (tty_con.buffer[0] == '\\')
            {
              for (i=0; i<=tty_con.cursor; i++)
              {
                tty_con.buffer[i] = tty_con.buffer[i+1];
              }
              tty_con.cursor--;
            }
          }
          tty_Show();
          return NULL;
        }
        avail = read(0, &key, 1);
        if (avail != -1)
        {
          // VT 100 keys
          if (key == '[' || key == 'O')
          {
            avail = read(0, &key, 1);
            if (avail != -1)
            {
              switch (key)
              {
              case 'A':
                history = Hist_Prev();
                if (history)
                {
                  tty_Hide();
                  tty_con = *history;
                  tty_Show();
                }
                tty_FlushIn();
                return NULL;
                break;
              case 'B':
                history = Hist_Next();
                tty_Hide();
                if (history)
                {
                  tty_con = *history;
                } else
                {
                  Field_Clear(&tty_con);
                }
                tty_Show();
                tty_FlushIn();
                return NULL;
                break;
              case 'C':
                return NULL;
              case 'D':
                return NULL;
              }
            }
          }
        }
        Com_DPrintf("droping ISCTL sequence: %d, tty_erase: %d\n", key, tty_erase);
        tty_FlushIn();
        return NULL;
      }
      // push regular character
      tty_con.buffer[tty_con.cursor] = key;
      tty_con.cursor++;
      // print the current line (this is differential)
      write(1, &key, 1);
    }
    return NULL;
  } else
  {
    int     len;
    fd_set  fdset;
    struct timeval timeout;

    if (!com_dedicated || !com_dedicated->value)
      return NULL;

    if (!stdin_active)
      return NULL;

    FD_ZERO(&fdset);
    FD_SET(0, &fdset); // stdin
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    if (select (1, &fdset, NULL, NULL, &timeout) == -1 || !FD_ISSET(0, &fdset))
    {
      return NULL;
    }

    len = read (0, text, sizeof(text));
    if (len == 0)
    { // eof!
      stdin_active = qfalse;
      return NULL;
    }

    if (len < 1)
      return NULL;
    text[len-1] = 0;    // rip off the /n and terminate

    return text;
  }
}