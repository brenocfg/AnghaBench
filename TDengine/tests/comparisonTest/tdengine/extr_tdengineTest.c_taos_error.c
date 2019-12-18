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
typedef  int /*<<< orphan*/  TAOS ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  taos_close (int /*<<< orphan*/ *) ; 
 char* taos_errstr (int /*<<< orphan*/ *) ; 

void taos_error(TAOS *con) {
  printf("TDengine error: %s\n", taos_errstr(con));
  taos_close(con);
  exit(1);
}