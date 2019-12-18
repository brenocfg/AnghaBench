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
struct callback_data {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* Argv0 ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* find_home_dir () ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int process_input (struct callback_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/  sqlite3_initialize () ; 
 char* sqlite3_mprintf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stdin_is_interactive ; 

__attribute__((used)) static int process_sqliterc(
  struct callback_data *p,        /* Configuration data */
  const char *sqliterc_override   /* Name of config file. NULL to use default */
){
  char *home_dir = NULL;
  const char *sqliterc = sqliterc_override;
  char *zBuf = 0;
  FILE *in = NULL;
  int rc = 0;

  if (sqliterc == NULL) {
    home_dir = find_home_dir();
    if( home_dir==0 ){
#if !defined(__RTP__) && !defined(_WRS_KERNEL)
      fprintf(stderr,"%s: Error: cannot locate your home directory\n", Argv0);
#endif
      return 1;
    }
    sqlite3_initialize();
    zBuf = sqlite3_mprintf("%s/.sqliterc",home_dir);
    sqliterc = zBuf;
  }
  in = fopen(sqliterc,"rb");
  if( in ){
    if( stdin_is_interactive ){
      fprintf(stderr,"-- Loading resources from %s\n",sqliterc);
    }
    rc = process_input(p,in);
    fclose(in);
  }
  sqlite3_free(zBuf);
  return rc;
}