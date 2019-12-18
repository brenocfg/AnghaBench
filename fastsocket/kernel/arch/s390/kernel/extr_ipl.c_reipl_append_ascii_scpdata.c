#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * scp_data; int /*<<< orphan*/  scp_data_len; } ;
struct TYPE_4__ {TYPE_1__ fcp; } ;
struct ipl_parameter_block {TYPE_2__ ipl_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  isascii (int /*<<< orphan*/ ) ; 
 scalar_t__ islower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 size_t min (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scpdata_length (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char tolower (int /*<<< orphan*/ ) ; 

size_t reipl_append_ascii_scpdata(char *dest, size_t size,
				  const struct ipl_parameter_block *ipb)
{
	size_t count;
	size_t i;
	int has_lowercase;

	count = min(size - 1, scpdata_length(ipb->ipl_info.fcp.scp_data,
					     ipb->ipl_info.fcp.scp_data_len));
	if (!count)
		goto out;

	has_lowercase = 0;
	for (i = 0; i < count; i++) {
		if (!isascii(ipb->ipl_info.fcp.scp_data[i])) {
			count = 0;
			goto out;
		}
		if (!has_lowercase && islower(ipb->ipl_info.fcp.scp_data[i]))
			has_lowercase = 1;
	}

	if (has_lowercase)
		memcpy(dest, ipb->ipl_info.fcp.scp_data, count);
	else
		for (i = 0; i < count; i++)
			dest[i] = tolower(ipb->ipl_info.fcp.scp_data[i]);
out:
	dest[count] = '\0';
	return count;
}