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
struct arguments {scalar_t__* file; int /*<<< orphan*/ * commands; int /*<<< orphan*/  database; int /*<<< orphan*/ * password; int /*<<< orphan*/ * user; int /*<<< orphan*/  host; scalar_t__ is_use_passwd; int /*<<< orphan*/ * timezone; } ;
typedef  int /*<<< orphan*/  TAOS ;

/* Variables and functions */
 char* CLIENT_VERSION ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 char* PROMPT_HEADER ; 
 char* SERVER_VERSION ; 
 int /*<<< orphan*/  TSDB_OPTION_TIMEZONE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * getpass (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  read_history () ; 
 int /*<<< orphan*/  shellRunCommand (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  source_file (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  stdout ; 
 char* strtok (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  taos_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * taos_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taos_get_client_info () ; 
 int /*<<< orphan*/  taos_get_server_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_init () ; 
 int /*<<< orphan*/  taos_options (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsDefaultPass ; 
 int /*<<< orphan*/ * tsDefaultUser ; 
 int tsMeterMetaKeepTimer ; 
 int tsMetricMetaKeepTimer ; 
 int /*<<< orphan*/  tsMgmtShellPort ; 
 int /*<<< orphan*/  write_history () ; 

TAOS *shellInit(struct arguments *args) {
  printf("\n");
  printf(CLIENT_VERSION, taos_get_client_info());
  fflush(stdout);

  // set options before initializing
  if (args->timezone != NULL) {
    taos_options(TSDB_OPTION_TIMEZONE, args->timezone);
  }

  if (args->is_use_passwd) {
    if (args->password == NULL) args->password = getpass("Enter password: ");
  } else {
    args->password = tsDefaultPass;
  }

  if (args->user == NULL) {
    args->user = tsDefaultUser;
  }

  taos_init();
  /*
   * set tsMetricMetaKeepTimer = 3000ms
   * set tsMeterMetaKeepTimer = 3000ms
   * means not save cache in shell
   */
  tsMetricMetaKeepTimer = 3;
  tsMeterMetaKeepTimer = 3000;

  // Connect to the database.
  TAOS *con = taos_connect(args->host, args->user, args->password, args->database, tsMgmtShellPort);
  if (con == NULL) {
    return con;
  }

  /* Read history TODO : release resources here*/
  read_history();

  // Check if it is temperory run
  if (args->commands != NULL || args->file[0] != 0) {
    if (args->commands != NULL) {
      char *token;
      token = strtok(args->commands, ";");
      while (token != NULL) {
        printf("%s%s\n", PROMPT_HEADER, token);
        shellRunCommand(con, token);
        token = strtok(NULL, ";");
      }
    }

    if (args->file[0] != 0) {
      source_file(con, args->file);
    }
    taos_close(con);

    write_history();
    exit(EXIT_SUCCESS);
  }

  printf(SERVER_VERSION, taos_get_server_info(con));

  return con;
}