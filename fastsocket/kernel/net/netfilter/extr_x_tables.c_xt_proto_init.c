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
typedef  size_t u_int8_t ;
struct proc_dir_entry {int dummy; } ;
struct net {int /*<<< orphan*/  proc_net; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FORMAT_MATCHES ; 
 int /*<<< orphan*/  FORMAT_TABLES ; 
 int /*<<< orphan*/  FORMAT_TARGETS ; 
 int XT_FUNCTION_MAXNAMELEN ; 
 struct proc_dir_entry* proc_create_data (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  proc_net_remove (struct net*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xt_match_ops ; 
 int /*<<< orphan*/ * xt_prefix ; 
 int /*<<< orphan*/  xt_table_ops ; 
 int /*<<< orphan*/  xt_target_ops ; 

int xt_proto_init(struct net *net, u_int8_t af)
{
#ifdef CONFIG_PROC_FS
	char buf[XT_FUNCTION_MAXNAMELEN];
	struct proc_dir_entry *proc;
#endif

	if (af >= ARRAY_SIZE(xt_prefix))
		return -EINVAL;


#ifdef CONFIG_PROC_FS
	strlcpy(buf, xt_prefix[af], sizeof(buf));
	strlcat(buf, FORMAT_TABLES, sizeof(buf));
	proc = proc_create_data(buf, 0440, net->proc_net, &xt_table_ops,
				(void *)(unsigned long)af);
	if (!proc)
		goto out;

	strlcpy(buf, xt_prefix[af], sizeof(buf));
	strlcat(buf, FORMAT_MATCHES, sizeof(buf));
	proc = proc_create_data(buf, 0440, net->proc_net, &xt_match_ops,
				(void *)(unsigned long)af);
	if (!proc)
		goto out_remove_tables;

	strlcpy(buf, xt_prefix[af], sizeof(buf));
	strlcat(buf, FORMAT_TARGETS, sizeof(buf));
	proc = proc_create_data(buf, 0440, net->proc_net, &xt_target_ops,
				(void *)(unsigned long)af);
	if (!proc)
		goto out_remove_matches;
#endif

	return 0;

#ifdef CONFIG_PROC_FS
out_remove_matches:
	strlcpy(buf, xt_prefix[af], sizeof(buf));
	strlcat(buf, FORMAT_MATCHES, sizeof(buf));
	proc_net_remove(net, buf);

out_remove_tables:
	strlcpy(buf, xt_prefix[af], sizeof(buf));
	strlcat(buf, FORMAT_TABLES, sizeof(buf));
	proc_net_remove(net, buf);
out:
	return -1;
#endif
}