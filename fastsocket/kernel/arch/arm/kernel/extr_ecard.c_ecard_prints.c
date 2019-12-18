#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  string; } ;
struct in_chunk_dir {TYPE_1__ d; } ;
struct TYPE_7__ {char* id; scalar_t__ cd; int /*<<< orphan*/  product; int /*<<< orphan*/  manufacturer; } ;
struct TYPE_8__ {char* card_desc; TYPE_2__ cid; scalar_t__ easi; int /*<<< orphan*/  slot_no; } ;
typedef  TYPE_3__ ecard_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ecard_readchunk (struct in_chunk_dir*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecard_prints(struct seq_file *m, ecard_t *ec)
{
	seq_printf(m, "  %d: %s ", ec->slot_no, ec->easi ? "EASI" : "    ");

	if (ec->cid.id == 0) {
		struct in_chunk_dir incd;

		seq_printf(m, "[%04X:%04X] ",
			ec->cid.manufacturer, ec->cid.product);

		if (!ec->card_desc && ec->cid.cd &&
		    ecard_readchunk(&incd, ec, 0xf5, 0)) {
			ec->card_desc = kmalloc(strlen(incd.d.string)+1, GFP_KERNEL);

			if (ec->card_desc)
				strcpy((char *)ec->card_desc, incd.d.string);
		}

		seq_printf(m, "%s\n", ec->card_desc ? ec->card_desc : "*unknown*");
	} else
		seq_printf(m, "Simple card %d\n", ec->cid.id);

	return 0;
}