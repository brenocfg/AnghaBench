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
typedef  int u16 ;
struct au1550_state {int /*<<< orphan*/  lock; } ;
struct ac97_codec {scalar_t__ private_data; } ;

/* Variables and functions */
 int POLL_COUNT ; 
 int /*<<< orphan*/  PSC_AC97CDC ; 
 scalar_t__ PSC_AC97CDC_INDX (int /*<<< orphan*/ ) ; 
 int PSC_AC97CDC_RD ; 
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

__attribute__((used)) static u16
rdcodec(struct ac97_codec *codec, u8 addr)
{
	struct au1550_state *s = (struct au1550_state *)codec->private_data;
	unsigned long   flags;
	u32             cmd, val;
	u16             data;
	int             i;

	spin_lock_irqsave(&s->lock, flags);

	for (i = 0; i < POLL_COUNT; i++) {
		val = au_readl(PSC_AC97STAT);
		au_sync();
		if (!(val & PSC_AC97STAT_CP))
			break;
	}
	if (i == POLL_COUNT)
		err("rdcodec: codec cmd pending expired!");

	cmd = (u32)PSC_AC97CDC_INDX(addr);
	cmd |= PSC_AC97CDC_RD;	/* read command */
	au_writel(cmd, PSC_AC97CDC);
	au_sync();

	/* now wait for the data
	*/
	for (i = 0; i < POLL_COUNT; i++) {
		val = au_readl(PSC_AC97STAT);
		au_sync();
		if (!(val & PSC_AC97STAT_CP))
			break;
	}
	if (i == POLL_COUNT) {
		err("rdcodec: read poll expired!");
		data = 0;
		goto out;
	}

	/* wait for command done?
	*/
	for (i = 0; i < POLL_COUNT; i++) {
		val = au_readl(PSC_AC97EVNT);
		au_sync();
		if (val & PSC_AC97EVNT_CD)
			break;
	}
	if (i == POLL_COUNT) {
		err("rdcodec: read cmdwait expired!");
		data = 0;
		goto out;
	}

	data = au_readl(PSC_AC97CDC) & 0xffff;
	au_sync();

	/* Clear command done event.
	*/
	au_writel(PSC_AC97EVNT_CD, PSC_AC97EVNT);
	au_sync();

 out:
	spin_unlock_irqrestore(&s->lock, flags);

	return data;
}