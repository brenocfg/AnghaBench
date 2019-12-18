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
typedef  int /*<<< orphan*/  FDFSMultiIP ;

/* Variables and functions */
 int fdfs_multi_ips_to_string_ex (int /*<<< orphan*/  const*,char const,char*,int const) ; 

__attribute__((used)) static inline int fdfs_multi_ips_to_string(const FDFSMultiIP *ip_addrs,
        char *buff, const int buffSize)
{
    const char seperator = ',';
    return fdfs_multi_ips_to_string_ex(ip_addrs, seperator, buff, buffSize);
}