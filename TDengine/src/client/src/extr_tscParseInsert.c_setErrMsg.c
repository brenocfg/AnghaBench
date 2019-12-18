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
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char const*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,scalar_t__) ; 
 scalar_t__ tListLen (char*) ; 

__attribute__((used)) static void setErrMsg(char *msg, const char *sql) {
  const char *  msgFormat = "near \"%s\" syntax error";
  const int32_t BACKWARD_CHAR_STEP = 15;

  // only extract part of sql string,avoid too long sql string cause stack over flow
  char buf[64] = {0};
  strncpy(buf, (sql - BACKWARD_CHAR_STEP), tListLen(buf) - 1);
  sprintf(msg, msgFormat, buf);
}