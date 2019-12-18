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
 int /*<<< orphan*/  BUSID_SIZE ; 
 int MAX_BUSID ; 
 scalar_t__** busid_table ; 
 int /*<<< orphan*/  busid_table_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (scalar_t__*,char const*,int /*<<< orphan*/ ) ; 

int match_busid(const char *busid)
{
	int i;

	spin_lock(&busid_table_lock);

	for (i = 0; i < MAX_BUSID; i++)
		if (busid_table[i][0])
			if (!strncmp(busid_table[i], busid, BUSID_SIZE)) {
				/* already registerd */
				spin_unlock(&busid_table_lock);
				return 0;
			}

	spin_unlock(&busid_table_lock);

	return 1;
}