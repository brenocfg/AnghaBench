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
typedef  int u32 ;
typedef  enum ixp23xx_irq_type { ____Placeholder_ixp23xx_irq_type } ixp23xx_irq_type ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_IXP23XX_GPIO6 ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 int* IXP23XX_GPIO_GPISR ; 
 scalar_t__ IXP23XX_GPIO_GPIT1R ; 
 scalar_t__ IXP23XX_GPIO_GPIT2R ; 
 int IXP23XX_GPIO_STYLE_ACTIVE_HIGH ; 
 int IXP23XX_GPIO_STYLE_ACTIVE_LOW ; 
 int IXP23XX_GPIO_STYLE_FALLING_EDGE ; 
 int IXP23XX_GPIO_STYLE_MASK ; 
 int IXP23XX_GPIO_STYLE_RISING_EDGE ; 
 int IXP23XX_GPIO_STYLE_SIZE ; 
 int IXP23XX_GPIO_STYLE_TRANSITIONAL ; 
 int IXP23XX_IRQ_EDGE ; 
 int IXP23XX_IRQ_LEVEL ; 
 int /*<<< orphan*/  ixp23xx_config_irq (unsigned int,int) ; 

__attribute__((used)) static int ixp23xx_irq_set_type(unsigned int irq, unsigned int type)
{
	int line = irq - IRQ_IXP23XX_GPIO6 + 6;
	u32 int_style;
	enum ixp23xx_irq_type irq_type;
	volatile u32 *int_reg;

	/*
	 * Only GPIOs 6-15 are wired to interrupts on IXP23xx
	 */
	if (line < 6 || line > 15)
		return -EINVAL;

	switch (type) {
	case IRQ_TYPE_EDGE_BOTH:
		int_style = IXP23XX_GPIO_STYLE_TRANSITIONAL;
		irq_type = IXP23XX_IRQ_EDGE;
		break;
	case IRQ_TYPE_EDGE_RISING:
		int_style = IXP23XX_GPIO_STYLE_RISING_EDGE;
		irq_type = IXP23XX_IRQ_EDGE;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		int_style = IXP23XX_GPIO_STYLE_FALLING_EDGE;
		irq_type = IXP23XX_IRQ_EDGE;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		int_style = IXP23XX_GPIO_STYLE_ACTIVE_HIGH;
		irq_type = IXP23XX_IRQ_LEVEL;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		int_style = IXP23XX_GPIO_STYLE_ACTIVE_LOW;
		irq_type = IXP23XX_IRQ_LEVEL;
		break;
	default:
		return -EINVAL;
	}

	ixp23xx_config_irq(irq, irq_type);

	if (line >= 8) {	/* pins 8-15 */
		line -= 8;
		int_reg = (volatile u32 *)IXP23XX_GPIO_GPIT2R;
	} else {		/* pins 0-7 */
		int_reg = (volatile u32 *)IXP23XX_GPIO_GPIT1R;
	}

	/*
	 * Clear pending interrupts
	 */
	*IXP23XX_GPIO_GPISR = (1 << line);

	/* Clear the style for the appropriate pin */
	*int_reg &= ~(IXP23XX_GPIO_STYLE_MASK <<
			(line * IXP23XX_GPIO_STYLE_SIZE));

	/* Set the new style */
	*int_reg |= (int_style << (line * IXP23XX_GPIO_STYLE_SIZE));

	return 0;
}