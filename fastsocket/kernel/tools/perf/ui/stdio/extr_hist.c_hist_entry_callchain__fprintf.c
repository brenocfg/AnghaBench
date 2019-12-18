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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  period; } ;
struct hist_entry {int /*<<< orphan*/  sorted_chain; TYPE_1__ stat; } ;
struct TYPE_4__ {int mode; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  CHAIN_FLAT 131 
#define  CHAIN_GRAPH_ABS 130 
#define  CHAIN_GRAPH_REL 129 
#define  CHAIN_NONE 128 
 size_t callchain__fprintf_flat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t callchain__fprintf_graph (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ callchain_param ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static size_t hist_entry_callchain__fprintf(struct hist_entry *he,
					    u64 total_samples, int left_margin,
					    FILE *fp)
{
	switch (callchain_param.mode) {
	case CHAIN_GRAPH_REL:
		return callchain__fprintf_graph(fp, &he->sorted_chain, he->stat.period,
						left_margin);
		break;
	case CHAIN_GRAPH_ABS:
		return callchain__fprintf_graph(fp, &he->sorted_chain, total_samples,
						left_margin);
		break;
	case CHAIN_FLAT:
		return callchain__fprintf_flat(fp, &he->sorted_chain, total_samples);
		break;
	case CHAIN_NONE:
		break;
	default:
		pr_err("Bad callchain mode\n");
	}

	return 0;
}