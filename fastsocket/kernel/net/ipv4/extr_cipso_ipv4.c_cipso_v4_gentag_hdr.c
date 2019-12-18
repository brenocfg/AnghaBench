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
typedef  unsigned char u32 ;
struct cipso_v4_doi {int /*<<< orphan*/  doi; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned char CIPSO_V4_HDR_LEN ; 
 unsigned char IPOPT_CIPSO ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cipso_v4_gentag_hdr(const struct cipso_v4_doi *doi_def,
				unsigned char *buf,
				u32 len)
{
	buf[0] = IPOPT_CIPSO;
	buf[1] = CIPSO_V4_HDR_LEN + len;
	*(__be32 *)&buf[2] = htonl(doi_def->doi);
}