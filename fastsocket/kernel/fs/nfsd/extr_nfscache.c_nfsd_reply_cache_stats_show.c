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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int rchits; int rcmisses; int rcnocache; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_lock ; 
 int drc_mem_usage ; 
 int longest_chain ; 
 int longest_chain_cachesize ; 
 int maskbits ; 
 int max_drc_entries ; 
 TYPE_1__ nfsdstats ; 
 int num_drc_entries ; 
 int payload_misses ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfsd_reply_cache_stats_show(struct seq_file *m, void *v)
{
	spin_lock(&cache_lock);
	seq_printf(m, "max entries:           %u\n", max_drc_entries);
	seq_printf(m, "num entries:           %u\n", num_drc_entries);
	seq_printf(m, "hash buckets:          %u\n", 1 << maskbits);
	seq_printf(m, "mem usage:             %u\n", drc_mem_usage);
	seq_printf(m, "cache hits:            %u\n", nfsdstats.rchits);
	seq_printf(m, "cache misses:          %u\n", nfsdstats.rcmisses);
	seq_printf(m, "not cached:            %u\n", nfsdstats.rcnocache);
	seq_printf(m, "payload misses:        %u\n", payload_misses);
	seq_printf(m, "longest chain len:     %u\n", longest_chain);
	seq_printf(m, "cachesize at longest:  %u\n", longest_chain_cachesize);
	spin_unlock(&cache_lock);
	return 0;
}