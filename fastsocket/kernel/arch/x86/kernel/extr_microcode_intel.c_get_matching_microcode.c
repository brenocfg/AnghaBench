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
struct microcode_header_intel {int /*<<< orphan*/  pf; int /*<<< orphan*/  sig; } ;
struct extended_sigtable {int count; } ;
struct extended_signature {int /*<<< orphan*/  pf; int /*<<< orphan*/  sig; } ;
struct cpu_signature {int dummy; } ;

/* Variables and functions */
 int EXT_HEADER_SIZE ; 
 unsigned long MC_HEADER_SIZE ; 
 long get_datasize (struct microcode_header_intel*) ; 
 unsigned long get_totalsize (struct microcode_header_intel*) ; 
 scalar_t__ update_match_cpu (struct cpu_signature*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_match_revision (struct microcode_header_intel*,int) ; 

__attribute__((used)) static int
get_matching_microcode(struct cpu_signature *cpu_sig, void *mc, int rev)
{
	struct microcode_header_intel *mc_header = mc;
	struct extended_sigtable *ext_header;
	unsigned long total_size = get_totalsize(mc_header);
	int ext_sigcount, i;
	struct extended_signature *ext_sig;

	if (!update_match_revision(mc_header, rev))
		return 0;

	if (update_match_cpu(cpu_sig, mc_header->sig, mc_header->pf))
		return 1;

	/* Look for ext. headers: */
	if (total_size <= get_datasize(mc_header) + MC_HEADER_SIZE)
		return 0;

	ext_header = mc + get_datasize(mc_header) + MC_HEADER_SIZE;
	ext_sigcount = ext_header->count;
	ext_sig = (void *)ext_header + EXT_HEADER_SIZE;

	for (i = 0; i < ext_sigcount; i++) {
		if (update_match_cpu(cpu_sig, ext_sig->sig, ext_sig->pf))
			return 1;
		ext_sig++;
	}
	return 0;
}