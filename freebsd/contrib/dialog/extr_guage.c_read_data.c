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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DLG_TRACE (char*) ; 
 size_t MY_LEN ; 
 int /*<<< orphan*/  dlg_trim_string (char*) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
read_data(char *buffer, FILE *fp)
{
    int result;

    if (feof(fp)) {
	result = 0;
    } else if (fgets(buffer, MY_LEN, fp) != 0) {
	DLG_TRACE(("read_data:%s", buffer));
	buffer[MY_LEN] = '\0';
	dlg_trim_string(buffer);
	result = 1;
    } else {
	result = -1;
    }
    return result;
}