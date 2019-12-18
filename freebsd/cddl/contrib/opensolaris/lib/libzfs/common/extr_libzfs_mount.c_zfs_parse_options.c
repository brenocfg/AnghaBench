#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t zfs_share_proto_t ;
struct TYPE_2__ {int /*<<< orphan*/  p_name; } ;

/* Variables and functions */
 int SA_CONFIG_ERR ; 
 int SA_OK ; 
 int _sa_parse_legacy_options (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* proto_table ; 

int
zfs_parse_options(char *options, zfs_share_proto_t proto)
{
#ifdef illumos
	if (_sa_parse_legacy_options != NULL) {
		return (_sa_parse_legacy_options(NULL, options,
		    proto_table[proto].p_name));
	}
	return (SA_CONFIG_ERR);
#else
	return (SA_OK);
#endif
}