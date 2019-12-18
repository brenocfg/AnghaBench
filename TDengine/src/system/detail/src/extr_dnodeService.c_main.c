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
struct sigaction {int /*<<< orphan*/  sa_sigaction; int /*<<< orphan*/  sa_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int LOG_CONS ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_LOCAL1 ; 
 int LOG_NDELAY ; 
 int LOG_PID ; 
 int /*<<< orphan*/  SA_SIGINFO ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 char* buildinfo ; 
 int /*<<< orphan*/  closelog () ; 
 char* compatible_version ; 
 char* configDir ; 
 int /*<<< orphan*/  dnodeCleanUpSystem () ; 
 scalar_t__ dnodeInitSystem () ; 
 int /*<<< orphan*/  dnodeParseParameterK () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* gitinfo ; 
 int /*<<< orphan*/  openlog (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 char* version ; 

int main(int argc, char *argv[]) {
  // Set global configuration file
  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-c") == 0) {
      if (i < argc - 1) {
        strcpy(configDir, argv[++i]);
      } else {
        printf("'-c' requires a parameter, default:%s\n", configDir);
        exit(EXIT_FAILURE);
      }
    } else if (strcmp(argv[i], "-V") == 0) {
      printf("version: %s compatible_version: %s\n", version, compatible_version);
      printf("gitinfo: %s\n", gitinfo);
      printf("buildinfo: %s\n", buildinfo);
      return 0;
    } else if (strcmp(argv[i], "-k") == 0) {
      dnodeParseParameterK();
    }
  }

  /* Set termination handler. */
  struct sigaction act;
  act.sa_flags = SA_SIGINFO;
  act.sa_sigaction = signal_handler;
  sigaction(SIGTERM, &act, NULL);
  sigaction(SIGHUP, &act, NULL);
  sigaction(SIGINT, &act, NULL);
  sigaction(SIGUSR1, &act, NULL);
  sigaction(SIGUSR2, &act, NULL);
  // sigaction(SIGABRT, &act, NULL);

  // Open /var/log/syslog file to record information.
  openlog("TDengine:", LOG_PID | LOG_CONS | LOG_NDELAY, LOG_LOCAL1);
  syslog(LOG_INFO, "Starting TDengine service...");

  // Initialize the system
  if (dnodeInitSystem() < 0) {
    syslog(LOG_ERR, "Error initialize TDengine system");
    closelog();

    dnodeCleanUpSystem();
    exit(EXIT_FAILURE);
  }

  syslog(LOG_INFO, "Started TDengine service successfully.");

  while (1) {
    sleep(1000);
  }
}