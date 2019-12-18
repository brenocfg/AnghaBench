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

/* Variables and functions */
 int BR_ERR_RECV_FATAL_ALERT ; 
 int BR_ERR_SEND_FATAL_ALERT ; 
 char* find_error_name (int,char const**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
print_error(int err)
{
	const char *name, *comment;

	name = find_error_name(err, &comment);
	if (name != NULL) {
		fprintf(stderr, "ERR %d: %s\n   %s\n", err, name, comment);
		return;
	}
	if (err >= BR_ERR_RECV_FATAL_ALERT
		&& err < BR_ERR_RECV_FATAL_ALERT + 256)
	{
		fprintf(stderr, "ERR %d: received fatal alert %d\n",
			err, err - BR_ERR_RECV_FATAL_ALERT);
		return;
	}
	if (err >= BR_ERR_SEND_FATAL_ALERT
		&& err < BR_ERR_SEND_FATAL_ALERT + 256)
	{
		fprintf(stderr, "ERR %d: sent fatal alert %d\n",
			err, err - BR_ERR_SEND_FATAL_ALERT);
		return;
	}
	fprintf(stderr, "ERR %d: UNKNOWN\n", err);
}