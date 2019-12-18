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
struct TYPE_4__ {int /*<<< orphan*/ ** we_wordv; } ;
typedef  TYPE_1__ wordexp_t ;
struct stat {int dummy; } ;

/* Variables and functions */
 int mkdir (char*,int) ; 
 int /*<<< orphan*/  pPrint (char*,char*,char*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wordexp (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wordfree (TYPE_1__*) ; 

void tsExpandFilePath(char* option_name, char* input_value) {
  wordexp_t full_path;
  wordexp(input_value, &full_path, 0);
  if (full_path.we_wordv != NULL && full_path.we_wordv[0] != NULL) {
    strcpy(input_value, full_path.we_wordv[0]);
  }
  wordfree(&full_path);

  struct stat dirstat;
  if (stat(input_value, &dirstat) < 0) {
    int code = mkdir(input_value, 0755);
    pPrint("config option:%s, input value:%s, directory not exist, create with return code:%d", option_name, input_value, code);
  }
}