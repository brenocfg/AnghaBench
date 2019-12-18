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
 int CURL_DO ; 
 int CURL_DONT ; 
 int CURL_IAC ; 
 int /*<<< orphan*/  CURL_TELCMD (int) ; 
 scalar_t__ CURL_TELCMD_OK (int) ; 
 char* CURL_TELOPT (int) ; 
 int CURL_TELOPT_EXOPL ; 
 scalar_t__ CURL_TELOPT_OK (int) ; 
 int CURL_WILL ; 
 int CURL_WONT ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,char const*,...) ; 

__attribute__((used)) static void printoption(struct Curl_easy *data,
                        const char *direction, int cmd, int option)
{
  if(data->set.verbose) {
    if(cmd == CURL_IAC) {
      if(CURL_TELCMD_OK(option))
        infof(data, "%s IAC %s\n", direction, CURL_TELCMD(option));
      else
        infof(data, "%s IAC %d\n", direction, option);
    }
    else {
      const char *fmt = (cmd == CURL_WILL) ? "WILL" :
                        (cmd == CURL_WONT) ? "WONT" :
                        (cmd == CURL_DO) ? "DO" :
                        (cmd == CURL_DONT) ? "DONT" : 0;
      if(fmt) {
        const char *opt;
        if(CURL_TELOPT_OK(option))
          opt = CURL_TELOPT(option);
        else if(option == CURL_TELOPT_EXOPL)
          opt = "EXOPL";
        else
          opt = NULL;

        if(opt)
          infof(data, "%s %s %s\n", direction, fmt, opt);
        else
          infof(data, "%s %s %d\n", direction, fmt, option);
      }
      else
        infof(data, "%s %d %d\n", direction, cmd, option);
    }
  }
}