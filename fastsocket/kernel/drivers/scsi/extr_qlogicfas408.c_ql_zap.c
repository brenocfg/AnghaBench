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
struct qlogicfas408_priv {int qbase; int int_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG0 ; 
 int /*<<< orphan*/  REG1 ; 
 int inb (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 

__attribute__((used)) static void ql_zap(struct qlogicfas408_priv *priv)
{
	int x;
	int qbase = priv->qbase;
	int int_type = priv->int_type;

	x = inb(qbase + 0xd);
	REG0;
	outb(3, qbase + 3);	/* reset SCSI */
	outb(2, qbase + 3);	/* reset chip */
	if (x & 0x80)
		REG1;
}