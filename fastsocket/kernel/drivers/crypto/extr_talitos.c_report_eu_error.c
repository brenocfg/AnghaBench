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
struct talitos_private {scalar_t__ reg; } ;
struct talitos_desc {int hdr; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  DESC_HDR_SEL0_AESU 139 
#define  DESC_HDR_SEL0_AFEU 138 
#define  DESC_HDR_SEL0_CRCU 137 
#define  DESC_HDR_SEL0_DEU 136 
#define  DESC_HDR_SEL0_KEU 135 
 int DESC_HDR_SEL0_MASK ; 
#define  DESC_HDR_SEL0_MDEUA 134 
#define  DESC_HDR_SEL0_MDEUB 133 
#define  DESC_HDR_SEL0_PKEU 132 
#define  DESC_HDR_SEL0_RNG 131 
#define  DESC_HDR_SEL1_CRCU 130 
 int DESC_HDR_SEL1_MASK ; 
#define  DESC_HDR_SEL1_MDEUA 129 
#define  DESC_HDR_SEL1_MDEUB 128 
 scalar_t__ TALITOS_AESUISR ; 
 scalar_t__ TALITOS_AESUISR_LO ; 
 scalar_t__ TALITOS_AFEUISR ; 
 scalar_t__ TALITOS_AFEUISR_LO ; 
 scalar_t__ TALITOS_CRCUISR ; 
 scalar_t__ TALITOS_CRCUISR_LO ; 
 scalar_t__ TALITOS_DESCBUF (int) ; 
 scalar_t__ TALITOS_DESCBUF_LO (int) ; 
 scalar_t__ TALITOS_DEUISR ; 
 scalar_t__ TALITOS_DEUISR_LO ; 
 scalar_t__ TALITOS_KEUISR ; 
 scalar_t__ TALITOS_KEUISR_LO ; 
 scalar_t__ TALITOS_MDEUISR ; 
 scalar_t__ TALITOS_MDEUISR_LO ; 
 scalar_t__ TALITOS_PKEUISR ; 
 scalar_t__ TALITOS_PKEUISR_LO ; 
 scalar_t__ TALITOS_RNGUISR ; 
 scalar_t__ TALITOS_RNGUISR_LO ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  in_be32 (scalar_t__) ; 

__attribute__((used)) static void report_eu_error(struct device *dev, int ch,
			    struct talitos_desc *desc)
{
	struct talitos_private *priv = dev_get_drvdata(dev);
	int i;

	switch (desc->hdr & DESC_HDR_SEL0_MASK) {
	case DESC_HDR_SEL0_AFEU:
		dev_err(dev, "AFEUISR 0x%08x_%08x\n",
			in_be32(priv->reg + TALITOS_AFEUISR),
			in_be32(priv->reg + TALITOS_AFEUISR_LO));
		break;
	case DESC_HDR_SEL0_DEU:
		dev_err(dev, "DEUISR 0x%08x_%08x\n",
			in_be32(priv->reg + TALITOS_DEUISR),
			in_be32(priv->reg + TALITOS_DEUISR_LO));
		break;
	case DESC_HDR_SEL0_MDEUA:
	case DESC_HDR_SEL0_MDEUB:
		dev_err(dev, "MDEUISR 0x%08x_%08x\n",
			in_be32(priv->reg + TALITOS_MDEUISR),
			in_be32(priv->reg + TALITOS_MDEUISR_LO));
		break;
	case DESC_HDR_SEL0_RNG:
		dev_err(dev, "RNGUISR 0x%08x_%08x\n",
			in_be32(priv->reg + TALITOS_RNGUISR),
			in_be32(priv->reg + TALITOS_RNGUISR_LO));
		break;
	case DESC_HDR_SEL0_PKEU:
		dev_err(dev, "PKEUISR 0x%08x_%08x\n",
			in_be32(priv->reg + TALITOS_PKEUISR),
			in_be32(priv->reg + TALITOS_PKEUISR_LO));
		break;
	case DESC_HDR_SEL0_AESU:
		dev_err(dev, "AESUISR 0x%08x_%08x\n",
			in_be32(priv->reg + TALITOS_AESUISR),
			in_be32(priv->reg + TALITOS_AESUISR_LO));
		break;
	case DESC_HDR_SEL0_CRCU:
		dev_err(dev, "CRCUISR 0x%08x_%08x\n",
			in_be32(priv->reg + TALITOS_CRCUISR),
			in_be32(priv->reg + TALITOS_CRCUISR_LO));
		break;
	case DESC_HDR_SEL0_KEU:
		dev_err(dev, "KEUISR 0x%08x_%08x\n",
			in_be32(priv->reg + TALITOS_KEUISR),
			in_be32(priv->reg + TALITOS_KEUISR_LO));
		break;
	}

	switch (desc->hdr & DESC_HDR_SEL1_MASK) {
	case DESC_HDR_SEL1_MDEUA:
	case DESC_HDR_SEL1_MDEUB:
		dev_err(dev, "MDEUISR 0x%08x_%08x\n",
			in_be32(priv->reg + TALITOS_MDEUISR),
			in_be32(priv->reg + TALITOS_MDEUISR_LO));
		break;
	case DESC_HDR_SEL1_CRCU:
		dev_err(dev, "CRCUISR 0x%08x_%08x\n",
			in_be32(priv->reg + TALITOS_CRCUISR),
			in_be32(priv->reg + TALITOS_CRCUISR_LO));
		break;
	}

	for (i = 0; i < 8; i++)
		dev_err(dev, "DESCBUF 0x%08x_%08x\n",
			in_be32(priv->reg + TALITOS_DESCBUF(ch) + 8*i),
			in_be32(priv->reg + TALITOS_DESCBUF_LO(ch) + 8*i));
}