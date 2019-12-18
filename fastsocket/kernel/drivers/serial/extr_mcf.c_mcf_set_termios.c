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
struct uart_port {int /*<<< orphan*/  lock; scalar_t__ membase; } ;
struct ktermios {int c_cflag; } ;

/* Variables and functions */
 int CMSPAR ; 
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 unsigned char MCFUART_MR1_CS5 ; 
 unsigned char MCFUART_MR1_CS6 ; 
 unsigned char MCFUART_MR1_CS7 ; 
 unsigned char MCFUART_MR1_CS8 ; 
 unsigned char MCFUART_MR1_PARITYEVEN ; 
 unsigned char MCFUART_MR1_PARITYMARK ; 
 unsigned char MCFUART_MR1_PARITYNONE ; 
 unsigned char MCFUART_MR1_PARITYODD ; 
 unsigned char MCFUART_MR1_PARITYSPACE ; 
 unsigned char MCFUART_MR1_RXERRCHAR ; 
 unsigned char MCFUART_MR1_RXIRQRDY ; 
 unsigned char MCFUART_MR1_RXRTS ; 
 unsigned char MCFUART_MR2_STOP1 ; 
 unsigned char MCFUART_MR2_STOP2 ; 
 unsigned char MCFUART_MR2_TXCTS ; 
 scalar_t__ MCFUART_UBG1 ; 
 scalar_t__ MCFUART_UBG2 ; 
 scalar_t__ MCFUART_UCR ; 
 unsigned int MCFUART_UCR_CMDRESETMRPTR ; 
 unsigned int MCFUART_UCR_CMDRESETRX ; 
 unsigned int MCFUART_UCR_CMDRESETTX ; 
 unsigned int MCFUART_UCR_RXENABLE ; 
 unsigned int MCFUART_UCR_TXENABLE ; 
 scalar_t__ MCFUART_UCSR ; 
 unsigned int MCFUART_UCSR_RXCLKTIMER ; 
 unsigned int MCFUART_UCSR_TXCLKTIMER ; 
 scalar_t__ MCFUART_UFPD ; 
 scalar_t__ MCFUART_UMR ; 
 unsigned int MCF_BUSCLK ; 
 int PARENB ; 
 int PARODD ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void mcf_set_termios(struct uart_port *port, struct ktermios *termios,
	struct ktermios *old)
{
	unsigned long flags;
	unsigned int baud, baudclk;
#if defined(CONFIG_M5272)
	unsigned int baudfr;
#endif
	unsigned char mr1, mr2;

	baud = uart_get_baud_rate(port, termios, old, 0, 230400);
#if defined(CONFIG_M5272)
	baudclk = (MCF_BUSCLK / baud) / 32;
	baudfr = (((MCF_BUSCLK / baud) + 1) / 2) % 16;
#else
	baudclk = ((MCF_BUSCLK / baud) + 16) / 32;
#endif

	mr1 = MCFUART_MR1_RXIRQRDY | MCFUART_MR1_RXERRCHAR;
	mr2 = 0;

	switch (termios->c_cflag & CSIZE) {
	case CS5: mr1 |= MCFUART_MR1_CS5; break;
	case CS6: mr1 |= MCFUART_MR1_CS6; break;
	case CS7: mr1 |= MCFUART_MR1_CS7; break;
	case CS8:
	default:  mr1 |= MCFUART_MR1_CS8; break;
	}

	if (termios->c_cflag & PARENB) {
		if (termios->c_cflag & CMSPAR) {
			if (termios->c_cflag & PARODD)
				mr1 |= MCFUART_MR1_PARITYMARK;
			else
				mr1 |= MCFUART_MR1_PARITYSPACE;
		} else {
			if (termios->c_cflag & PARODD)
				mr1 |= MCFUART_MR1_PARITYODD;
			else
				mr1 |= MCFUART_MR1_PARITYEVEN;
		}
	} else {
		mr1 |= MCFUART_MR1_PARITYNONE;
	}

	if (termios->c_cflag & CSTOPB)
		mr2 |= MCFUART_MR2_STOP2;
	else
		mr2 |= MCFUART_MR2_STOP1;

	if (termios->c_cflag & CRTSCTS) {
		mr1 |= MCFUART_MR1_RXRTS;
		mr2 |= MCFUART_MR2_TXCTS;
	}

	spin_lock_irqsave(&port->lock, flags);
	writeb(MCFUART_UCR_CMDRESETRX, port->membase + MCFUART_UCR);
	writeb(MCFUART_UCR_CMDRESETTX, port->membase + MCFUART_UCR);
	writeb(MCFUART_UCR_CMDRESETMRPTR, port->membase + MCFUART_UCR);
	writeb(mr1, port->membase + MCFUART_UMR);
	writeb(mr2, port->membase + MCFUART_UMR);
	writeb((baudclk & 0xff00) >> 8, port->membase + MCFUART_UBG1);
	writeb((baudclk & 0xff), port->membase + MCFUART_UBG2);
#if defined(CONFIG_M5272)
	writeb((baudfr & 0x0f), port->membase + MCFUART_UFPD);
#endif
	writeb(MCFUART_UCSR_RXCLKTIMER | MCFUART_UCSR_TXCLKTIMER,
		port->membase + MCFUART_UCSR);
	writeb(MCFUART_UCR_RXENABLE | MCFUART_UCR_TXENABLE,
		port->membase + MCFUART_UCR);
	spin_unlock_irqrestore(&port->lock, flags);
}