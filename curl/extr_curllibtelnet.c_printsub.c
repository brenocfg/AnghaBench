#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ verbose; } ;
struct Curl_easy {TYPE_1__ set; } ;

/* Variables and functions */
 unsigned int CURL_IAC ; 
#define  CURL_NEW_ENV_VALUE 137 
#define  CURL_NEW_ENV_VAR 136 
 int CURL_SE ; 
 int /*<<< orphan*/  CURL_TELCMD (int) ; 
 scalar_t__ CURL_TELCMD_OK (int) ; 
 int /*<<< orphan*/  CURL_TELOPT (unsigned char) ; 
#define  CURL_TELOPT_NAWS 135 
#define  CURL_TELOPT_NEW_ENVIRON 134 
 scalar_t__ CURL_TELOPT_OK (unsigned char) ; 
#define  CURL_TELOPT_TTYPE 133 
#define  CURL_TELOPT_XDISPLOC 132 
#define  CURL_TELQUAL_INFO 131 
#define  CURL_TELQUAL_IS 130 
#define  CURL_TELQUAL_NAME 129 
#define  CURL_TELQUAL_SEND 128 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,...) ; 

__attribute__((used)) static void printsub(struct Curl_easy *data,
                     int direction,             /* '<' or '>' */
                     unsigned char *pointer,    /* where suboption data is */
                     size_t length)             /* length of suboption data */
{
  if(data->set.verbose) {
    unsigned int i = 0;
    if(direction) {
      infof(data, "%s IAC SB ", (direction == '<')? "RCVD":"SENT");
      if(length >= 3) {
        int j;

        i = pointer[length-2];
        j = pointer[length-1];

        if(i != CURL_IAC || j != CURL_SE) {
          infof(data, "(terminated by ");
          if(CURL_TELOPT_OK(i))
            infof(data, "%s ", CURL_TELOPT(i));
          else if(CURL_TELCMD_OK(i))
            infof(data, "%s ", CURL_TELCMD(i));
          else
            infof(data, "%u ", i);
          if(CURL_TELOPT_OK(j))
            infof(data, "%s", CURL_TELOPT(j));
          else if(CURL_TELCMD_OK(j))
            infof(data, "%s", CURL_TELCMD(j));
          else
            infof(data, "%d", j);
          infof(data, ", not IAC SE!) ");
        }
      }
      length -= 2;
    }
    if(length < 1) {
      infof(data, "(Empty suboption?)");
      return;
    }

    if(CURL_TELOPT_OK(pointer[0])) {
      switch(pointer[0]) {
      case CURL_TELOPT_TTYPE:
      case CURL_TELOPT_XDISPLOC:
      case CURL_TELOPT_NEW_ENVIRON:
      case CURL_TELOPT_NAWS:
        infof(data, "%s", CURL_TELOPT(pointer[0]));
        break;
      default:
        infof(data, "%s (unsupported)", CURL_TELOPT(pointer[0]));
        break;
      }
    }
    else
      infof(data, "%d (unknown)", pointer[i]);

    switch(pointer[0]) {
    case CURL_TELOPT_NAWS:
      if(length > 4)
        infof(data, "Width: %d ; Height: %d", (pointer[1]<<8) | pointer[2],
              (pointer[3]<<8) | pointer[4]);
      break;
    default:
      switch(pointer[1]) {
      case CURL_TELQUAL_IS:
        infof(data, " IS");
        break;
      case CURL_TELQUAL_SEND:
        infof(data, " SEND");
        break;
      case CURL_TELQUAL_INFO:
        infof(data, " INFO/REPLY");
        break;
      case CURL_TELQUAL_NAME:
        infof(data, " NAME");
        break;
      }

      switch(pointer[0]) {
      case CURL_TELOPT_TTYPE:
      case CURL_TELOPT_XDISPLOC:
        pointer[length] = 0;
        infof(data, " \"%s\"", &pointer[2]);
        break;
      case CURL_TELOPT_NEW_ENVIRON:
        if(pointer[1] == CURL_TELQUAL_IS) {
          infof(data, " ");
          for(i = 3; i < length; i++) {
            switch(pointer[i]) {
            case CURL_NEW_ENV_VAR:
              infof(data, ", ");
              break;
            case CURL_NEW_ENV_VALUE:
              infof(data, " = ");
              break;
            default:
              infof(data, "%c", pointer[i]);
              break;
            }
          }
        }
        break;
      default:
        for(i = 2; i < length; i++)
          infof(data, " %.2x", pointer[i]);
        break;
      }
    }
    if(direction)
      infof(data, "\n");
  }
}