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
struct smb_hdr {int /*<<< orphan*/  smb_buf_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  be32_add_cpu (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void inc_rfc1001_len(void *pSMB, int count)
{
	struct smb_hdr *hdr = (struct smb_hdr *)pSMB;

	be32_add_cpu(&hdr->smb_buf_length, count);
}