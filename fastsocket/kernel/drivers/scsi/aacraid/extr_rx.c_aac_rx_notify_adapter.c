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
typedef  int u32 ;
struct aac_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  IDR; } ;

/* Variables and functions */
#define  AdapNormCmdQue 134 
#define  AdapNormRespQue 133 
#define  AdapPrintfDone 132 
 int /*<<< orphan*/  BUG () ; 
#define  FastIo 131 
#define  HostNormCmdNotFull 130 
#define  HostNormRespNotFull 129 
#define  HostShutdown 128 
 int /*<<< orphan*/  INBOUNDDOORBELL_1 ; 
 int /*<<< orphan*/  INBOUNDDOORBELL_2 ; 
 int /*<<< orphan*/  INBOUNDDOORBELL_3 ; 
 int /*<<< orphan*/  INBOUNDDOORBELL_4 ; 
 int /*<<< orphan*/  INBOUNDDOORBELL_5 ; 
 int /*<<< orphan*/  INBOUNDDOORBELL_6 ; 
 TYPE_1__ MUnit ; 
 int /*<<< orphan*/  rx_writel (struct aac_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aac_rx_notify_adapter(struct aac_dev *dev, u32 event)
{
	switch (event) {

	case AdapNormCmdQue:
		rx_writel(dev, MUnit.IDR,INBOUNDDOORBELL_1);
		break;
	case HostNormRespNotFull:
		rx_writel(dev, MUnit.IDR,INBOUNDDOORBELL_4);
		break;
	case AdapNormRespQue:
		rx_writel(dev, MUnit.IDR,INBOUNDDOORBELL_2);
		break;
	case HostNormCmdNotFull:
		rx_writel(dev, MUnit.IDR,INBOUNDDOORBELL_3);
		break;
	case HostShutdown:
		break;
	case FastIo:
		rx_writel(dev, MUnit.IDR,INBOUNDDOORBELL_6);
		break;
	case AdapPrintfDone:
		rx_writel(dev, MUnit.IDR,INBOUNDDOORBELL_5);
		break;
	default:
		BUG();
		break;
	}
}