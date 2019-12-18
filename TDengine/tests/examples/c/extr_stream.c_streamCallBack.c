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
typedef  int /*<<< orphan*/  TAOS_ROW ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  int /*<<< orphan*/  TAOS_FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/ * taos_fetch_fields (int /*<<< orphan*/ *) ; 
 int taos_num_fields (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_print_row (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void streamCallBack(void *param, TAOS_RES *res, TAOS_ROW row)
{
  // in this simple demo, it just print out the result
  char temp[128];

  TAOS_FIELD *fields = taos_fetch_fields(res);
  int         numFields = taos_num_fields(res);

  taos_print_row(temp, row, fields, numFields);

  printf("\n%s\n", temp);
}