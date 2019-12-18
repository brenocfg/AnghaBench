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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct au1550_state {int /*<<< orphan*/  lock; } ;
struct ac97_codec {scalar_t__ private_data; } ;

/* Variables and functions */
 int POLL_COUNT ; 
 int /*<<< orphan*/  PSC_AC97CDC ; 
 scalar_t__ PSC_AC97CDC_INDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSC_AC97EVNT ; 
 int PSC_AC97EVNT_CD ; 
 int /*<<< orphan*/  PSC_AC97STAT ; 
 int PSC_AC97STAT_CP ; 
 int au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
wrcodec(struct ac97_codec *codec, u8 addr, u16 data)
{
	struct au1550_state *s = (struct au1550_state *)codec->private_data;
	unsigned long   flags;
	u32             cmd, val;
	int             i;

	spin_lock_irqsave(&s->lock, flags);

	for (i = 0; i < POLL_COUNT; i++) {
		val = au_readl(PSC_AC97STAT);
		au_sync();
		if (!(val & PSC_AC97STAT_CP))
			break;
	}
	if (i == POLL_COUNT)
		err("wrcodec: codec cmd pending expired!");

	cmd = (u32)PSC_AC97CDC_INDX(addr);
	cmd |= (u32)data;
	au_writel(cmd, PSC_AC97CDC);
	au_sync();

	for (i = 0; i < POLL_COUNT; i++) {
		val = au_readl(PSC_AC97STAT);
		au_sync();
		if (!(val & PSC_AC97STAT_CP))
			break;
	}
	if (i == POLL_COUNT)
		err("wrcodec: codec cmd pending expired!");

	for (i = 0; i < POLL_COUNT; i++) {
		val = au_readl(PSC_AC97EVNT);
		au_sync();
		if (val & PSC_AC97EVNT_CD)
			break;
	}
	if (i == POLL_COUNT)
		err("wrcodec: read cmdwait expired!");

	/* Clear command done event.
	*/
	au_writel(PSC_AC97EVNT_CD, PSC_AC97EVNT);
	au_sync();

	spin_unlock_irqrestore(&s->lock, flags);
}