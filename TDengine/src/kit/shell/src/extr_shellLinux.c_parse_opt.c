#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * we_wordv; } ;
typedef  TYPE_1__ wordexp_t ;
struct arguments {char* host; int is_use_passwd; char* password; char* timezone; char* user; char* commands; int is_raw_time; char* database; int abort; int /*<<< orphan*/  file; } ;
struct argp_state {struct arguments* input; } ;
typedef  int error_t ;

/* Variables and functions */
 int ARGP_ERR_UNKNOWN ; 
#define  OPT_ABORT 128 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  configDir ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsMgmtShellPort ; 
 int /*<<< orphan*/  wordexp (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wordfree (TYPE_1__*) ; 

__attribute__((used)) static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  /* Get the input argument from argp_parse, which we
  know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;
  wordexp_t full_path;

  switch (key) {
    case 'h':
      arguments->host = arg;
      break;
    case 'p':
      arguments->is_use_passwd = true;
      if (arg) arguments->password = arg;
      break;
    case 'P':
      tsMgmtShellPort = atoi(arg);
      break;
    case 't':
      arguments->timezone = arg;
      break;
    case 'u':
      arguments->user = arg;
      break;
    case 'c':
      if (wordexp(arg, &full_path, 0) != 0) {
        fprintf(stderr, "Invalid path %s\n", arg);
        return -1;
      }
      strcpy(configDir, full_path.we_wordv[0]);
      wordfree(&full_path);
      break;
    case 's':
      arguments->commands = arg;
      break;
    case 'r':
      arguments->is_raw_time = true;
      break;
    case 'f':
      if (wordexp(arg, &full_path, 0) != 0) {
        fprintf(stderr, "Invalid path %s\n", arg);
        return -1;
      }
      strcpy(arguments->file, full_path.we_wordv[0]);
      wordfree(&full_path);
      break;
    case 'd':
      arguments->database = arg;
      break;
    case OPT_ABORT:
      arguments->abort = 1;
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}