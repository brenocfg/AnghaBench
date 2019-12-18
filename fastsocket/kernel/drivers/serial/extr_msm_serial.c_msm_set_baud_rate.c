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
struct uart_port {int fifosize; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_CSR ; 
 unsigned int UART_CSR_115200 ; 
 unsigned int UART_CSR_1200 ; 
 unsigned int UART_CSR_14400 ; 
 unsigned int UART_CSR_19200 ; 
 unsigned int UART_CSR_2400 ; 
 unsigned int UART_CSR_28800 ; 
 unsigned int UART_CSR_300 ; 
 unsigned int UART_CSR_38400 ; 
 unsigned int UART_CSR_4800 ; 
 unsigned int UART_CSR_57600 ; 
 unsigned int UART_CSR_600 ; 
 unsigned int UART_CSR_9600 ; 
 int /*<<< orphan*/  UART_IPR ; 
 unsigned int UART_IPR_RXSTALE_LAST ; 
 unsigned int UART_IPR_STALE_LSB ; 
 unsigned int UART_IPR_STALE_TIMEOUT_MSB ; 
 int /*<<< orphan*/  UART_RFWR ; 
 int /*<<< orphan*/  UART_TFWR ; 
 int /*<<< orphan*/  msm_write (struct uart_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msm_set_baud_rate(struct uart_port *port, unsigned int baud)
{
	unsigned int baud_code, rxstale, watermark;

	switch (baud) {
	case 300:
		baud_code = UART_CSR_300;
		rxstale = 1;
		break;
	case 600:
		baud_code = UART_CSR_600;
		rxstale = 1;
		break;
	case 1200:
		baud_code = UART_CSR_1200;
		rxstale = 1;
		break;
	case 2400:
		baud_code = UART_CSR_2400;
		rxstale = 1;
		break;
	case 4800:
		baud_code = UART_CSR_4800;
		rxstale = 1;
		break;
	case 9600:
		baud_code = UART_CSR_9600;
		rxstale = 2;
		break;
	case 14400:
		baud_code = UART_CSR_14400;
		rxstale = 3;
		break;
	case 19200:
		baud_code = UART_CSR_19200;
		rxstale = 4;
		break;
	case 28800:
		baud_code = UART_CSR_28800;
		rxstale = 6;
		break;
	case 38400:
		baud_code = UART_CSR_38400;
		rxstale = 8;
		break;
	case 57600:
		baud_code = UART_CSR_57600;
		rxstale = 16;
		break;
	case 115200:
	default:
		baud_code = UART_CSR_115200;
		baud = 115200;
		rxstale = 31;
		break;
	}

	msm_write(port, baud_code, UART_CSR);

	/* RX stale watermark */
	watermark = UART_IPR_STALE_LSB & rxstale;
	watermark |= UART_IPR_RXSTALE_LAST;
	watermark |= UART_IPR_STALE_TIMEOUT_MSB & (rxstale << 2);
	msm_write(port, watermark, UART_IPR);

	/* set RX watermark */
	watermark = (port->fifosize * 3) / 4;
	msm_write(port, watermark, UART_RFWR);

	/* set TX watermark */
	msm_write(port, 10, UART_TFWR);

	return baud;
}