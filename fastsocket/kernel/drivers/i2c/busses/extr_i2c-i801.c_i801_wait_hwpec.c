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
struct i801_priv {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MAX_TIMEOUT ; 
 int /*<<< orphan*/  SMBHSTSTS (struct i801_priv*) ; 
 int SMBHSTSTS_INTR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i801_wait_hwpec(struct i801_priv *priv)
{
	int timeout = 0;
	int status;

	do {
		msleep(1);
		status = inb_p(SMBHSTSTS(priv));
	} while ((!(status & SMBHSTSTS_INTR))
		 && (timeout++ < MAX_TIMEOUT));

	if (timeout > MAX_TIMEOUT)
		dev_dbg(&priv->pci_dev->dev, "PEC Timeout!\n");

	outb_p(status, SMBHSTSTS(priv));
}