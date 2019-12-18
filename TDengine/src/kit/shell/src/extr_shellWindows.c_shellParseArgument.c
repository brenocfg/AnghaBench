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
struct arguments {char* host; int is_use_passwd; char* user; char* commands; int is_raw_time; char* database; char* timezone; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  configDir ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printHelp () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tsMgmtShellPort ; 

void shellParseArgument(int argc, char *argv[], struct arguments *arguments) {
  for (int i = 1; i < argc; i++) {
    // for host
    if (strcmp(argv[i], "-h") == 0) {
      if (i < argc - 1) {
        arguments->host = argv[++i];
      } else {
        fprintf(stderr, "option -h requires an argument\n");
        exit(EXIT_FAILURE);
      }
    }
    // for password
    else if (strcmp(argv[i], "-p") == 0) {
      arguments->is_use_passwd = true;
    }
    // for management port
    else if (strcmp(argv[i], "-P") == 0) {
      if (i < argc - 1) {
        tsMgmtShellPort = atoi(argv[++i]);
      } else {
        fprintf(stderr, "option -P requires an argument\n");
        exit(EXIT_FAILURE);
      }
    }
    // for user
    else if (strcmp(argv[i], "-u") == 0) {
      if (i < argc - 1) {
        arguments->user = argv[++i];
      } else {
        fprintf(stderr, "option -u requires an argument\n");
        exit(EXIT_FAILURE);
      }
    } else if (strcmp(argv[i], "-c") == 0) {
      if (i < argc - 1) {
        strcpy(configDir, argv[++i]);
      } else {
        fprintf(stderr, "Option -c requires an argument\n");
        exit(EXIT_FAILURE);
      }
    } else if (strcmp(argv[i], "-s") == 0) {
      if (i < argc - 1) {
        arguments->commands = argv[++i];
      } else {
        fprintf(stderr, "option -s requires an argument\n");
        exit(EXIT_FAILURE);
      }
    } else if (strcmp(argv[i], "-r") == 0) {
      arguments->is_raw_time = true;
    }
    // For temperory batch commands to run TODO
    else if (strcmp(argv[i], "-f") == 0) {
      if (i < argc - 1) {
        strcpy(arguments->file, argv[++i]);
      } else {
        fprintf(stderr, "option -f requires an argument\n");
        exit(EXIT_FAILURE);
      }
    }
    // for default database
    else if (strcmp(argv[i], "-d") == 0) {
      if (i < argc - 1) {
        arguments->database = argv[++i];
      } else {
        fprintf(stderr, "option -d requires an argument\n");
        exit(EXIT_FAILURE);
      }
    }
    // For time zone
    else if (strcmp(argv[i], "-t") == 0) {
      if (i < argc - 1) {
        arguments->timezone = argv[++i];
      } else {
        fprintf(stderr, "option -t requires an argument\n");
        exit(EXIT_FAILURE);
      }
    }
    // For temperory command TODO
    else if (strcmp(argv[i], "--help") == 0) {
      printHelp();
      exit(EXIT_FAILURE);
    } else {
      fprintf(stderr, "wrong options\n");
      printHelp();
      exit(EXIT_FAILURE);
    }
  }
}