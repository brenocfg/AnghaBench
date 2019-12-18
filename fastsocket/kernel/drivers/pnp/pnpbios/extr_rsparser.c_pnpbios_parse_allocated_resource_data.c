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
struct pnp_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IORESOURCE_DISABLED ; 
 unsigned char LARGE_TAG ; 
#define  LARGE_TAG_ANSISTR 138 
#define  LARGE_TAG_FIXEDMEM32 137 
#define  LARGE_TAG_MEM 136 
#define  LARGE_TAG_MEM32 135 
#define  LARGE_TAG_VENDOR 134 
#define  SMALL_TAG_DMA 133 
#define  SMALL_TAG_END 132 
#define  SMALL_TAG_FIXEDPORT 131 
#define  SMALL_TAG_IRQ 130 
#define  SMALL_TAG_PORT 129 
#define  SMALL_TAG_VENDOR 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  pcibios_penalize_isa_irq (int,int) ; 
 int /*<<< orphan*/  pnp_add_dma_resource (struct pnp_dev*,int,int) ; 
 int /*<<< orphan*/  pnp_add_irq_resource (struct pnp_dev*,int,int) ; 
 int /*<<< orphan*/  pnp_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pnp_init_resources (struct pnp_dev*) ; 
 int /*<<< orphan*/  pnpbios_parse_allocated_ioresource (struct pnp_dev*,int,int) ; 
 int /*<<< orphan*/  pnpbios_parse_allocated_memresource (struct pnp_dev*,int,int) ; 

__attribute__((used)) static unsigned char *pnpbios_parse_allocated_resource_data(struct pnp_dev *dev,
							    unsigned char *p,
							    unsigned char *end)
{
	unsigned int len, tag;
	int io, size, mask, i, flags;

	if (!p)
		return NULL;

	pnp_dbg(&dev->dev, "parse allocated resources\n");

	pnp_init_resources(dev);

	while ((char *)p < (char *)end) {

		/* determine the type of tag */
		if (p[0] & LARGE_TAG) {	/* large tag */
			len = (p[2] << 8) | p[1];
			tag = p[0];
		} else {	/* small tag */
			len = p[0] & 0x07;
			tag = ((p[0] >> 3) & 0x0f);
		}

		switch (tag) {

		case LARGE_TAG_MEM:
			if (len != 9)
				goto len_err;
			io = *(short *)&p[4];
			size = *(short *)&p[10];
			pnpbios_parse_allocated_memresource(dev, io, size);
			break;

		case LARGE_TAG_ANSISTR:
			/* ignore this for now */
			break;

		case LARGE_TAG_VENDOR:
			/* do nothing */
			break;

		case LARGE_TAG_MEM32:
			if (len != 17)
				goto len_err;
			io = *(int *)&p[4];
			size = *(int *)&p[16];
			pnpbios_parse_allocated_memresource(dev, io, size);
			break;

		case LARGE_TAG_FIXEDMEM32:
			if (len != 9)
				goto len_err;
			io = *(int *)&p[4];
			size = *(int *)&p[8];
			pnpbios_parse_allocated_memresource(dev, io, size);
			break;

		case SMALL_TAG_IRQ:
			if (len < 2 || len > 3)
				goto len_err;
			flags = 0;
			io = -1;
			mask = p[1] + p[2] * 256;
			for (i = 0; i < 16; i++, mask = mask >> 1)
				if (mask & 0x01)
					io = i;
			if (io != -1)
				pcibios_penalize_isa_irq(io, 1);
			else
				flags = IORESOURCE_DISABLED;
			pnp_add_irq_resource(dev, io, flags);
			break;

		case SMALL_TAG_DMA:
			if (len != 2)
				goto len_err;
			flags = 0;
			io = -1;
			mask = p[1];
			for (i = 0; i < 8; i++, mask = mask >> 1)
				if (mask & 0x01)
					io = i;
			if (io == -1)
				flags = IORESOURCE_DISABLED;
			pnp_add_dma_resource(dev, io, flags);
			break;

		case SMALL_TAG_PORT:
			if (len != 7)
				goto len_err;
			io = p[2] + p[3] * 256;
			size = p[7];
			pnpbios_parse_allocated_ioresource(dev, io, size);
			break;

		case SMALL_TAG_VENDOR:
			/* do nothing */
			break;

		case SMALL_TAG_FIXEDPORT:
			if (len != 3)
				goto len_err;
			io = p[1] + p[2] * 256;
			size = p[3];
			pnpbios_parse_allocated_ioresource(dev, io, size);
			break;

		case SMALL_TAG_END:
			p = p + 2;
			return (unsigned char *)p;
			break;

		default:	/* an unkown tag */
len_err:
			dev_err(&dev->dev, "unknown tag %#x length %d\n",
				tag, len);
			break;
		}

		/* continue to the next tag */
		if (p[0] & LARGE_TAG)
			p += len + 3;
		else
			p += len + 1;
	}

	dev_err(&dev->dev, "no end tag in resource structure\n");

	return NULL;
}