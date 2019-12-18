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
struct microtune_priv {int dummy; } ;
struct dvb_frontend {struct microtune_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  tuner_dbg (char*,int,...) ; 

__attribute__((used)) static int mt2032_spurcheck(struct dvb_frontend *fe,
			    int f1, int f2, int spectrum_from,int spectrum_to)
{
	struct microtune_priv *priv = fe->tuner_priv;
	int n1=1,n2,f;

	f1=f1/1000; //scale to kHz to avoid 32bit overflows
	f2=f2/1000;
	spectrum_from/=1000;
	spectrum_to/=1000;

	tuner_dbg("spurcheck f1=%d f2=%d  from=%d to=%d\n",
		  f1,f2,spectrum_from,spectrum_to);

	do {
	    n2=-n1;
	    f=n1*(f1-f2);
	    do {
		n2--;
		f=f-f2;
		tuner_dbg("spurtest n1=%d n2=%d ftest=%d\n",n1,n2,f);

		if( (f>spectrum_from) && (f<spectrum_to))
			tuner_dbg("mt2032 spurcheck triggered: %d\n",n1);
	    } while ( (f>(f2-spectrum_to)) || (n2>-5));
	    n1++;
	} while (n1<5);

	return 1;
}