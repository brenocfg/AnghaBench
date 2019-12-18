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
struct dlm_header {int /*<<< orphan*/  h_length; void* h_nodeid; void* h_lockspace; void* h_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (void*) ; 

__attribute__((used)) static void header_in(struct dlm_header *hd)
{
	hd->h_version		= le32_to_cpu(hd->h_version);
	hd->h_lockspace		= le32_to_cpu(hd->h_lockspace);
	hd->h_nodeid		= le32_to_cpu(hd->h_nodeid);
	hd->h_length		= le16_to_cpu(hd->h_length);
}