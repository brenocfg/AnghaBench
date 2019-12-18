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
struct sigaction {int /*<<< orphan*/  sa_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  checkVersion () ; 
 int /*<<< orphan*/ * con ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interruptHandler ; 
 int /*<<< orphan*/  pid ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shellGetGrantInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * shellInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shellLoopQuery ; 
 int /*<<< orphan*/  shellParseArgument (int,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_error (int /*<<< orphan*/ *) ; 

int main(int argc, char* argv[]) {
  /*setlocale(LC_ALL, "en_US.UTF-8"); */

  if (!checkVersion()) {
    exit(EXIT_FAILURE);
  }

  shellParseArgument(argc, argv, &args);

  /* Initialize the shell */
  con = shellInit(&args);
  if (con == NULL) {
    taos_error(con);
    exit(EXIT_FAILURE);
  }

  /* Interupt handler. */
  struct sigaction act;
  act.sa_handler = interruptHandler;
  sigaction(SIGTERM, &act, NULL);
  sigaction(SIGINT, &act, NULL);

  /* Get grant information */
  shellGetGrantInfo(con);

  /* Loop to query the input. */
  while (1) {
    pthread_create(&pid, NULL, shellLoopQuery, con);
    pthread_join(pid, NULL);
  }
  return 0;
}