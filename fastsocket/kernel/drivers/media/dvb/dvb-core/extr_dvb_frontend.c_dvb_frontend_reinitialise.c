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
struct dvb_frontend_private {int reinitialise; } ;
struct dvb_frontend {struct dvb_frontend_private* frontend_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_frontend_wakeup (struct dvb_frontend*) ; 

void dvb_frontend_reinitialise(struct dvb_frontend *fe)
{
	struct dvb_frontend_private *fepriv = fe->frontend_priv;

	fepriv->reinitialise = 1;
	dvb_frontend_wakeup(fe);
}