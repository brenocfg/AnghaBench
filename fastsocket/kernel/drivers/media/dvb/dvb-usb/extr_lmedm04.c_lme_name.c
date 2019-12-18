#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct lme2510_state {size_t tuner_config; } ;
struct dvb_usb_adapter {TYPE_5__* fe; TYPE_2__* dev; } ;
struct TYPE_8__ {char* name; } ;
struct TYPE_9__ {TYPE_3__ info; } ;
struct TYPE_10__ {TYPE_4__ ops; } ;
struct TYPE_7__ {TYPE_1__* desc; struct lme2510_state* priv; } ;
struct TYPE_6__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static int lme_name(struct dvb_usb_adapter *adap)
{
	struct lme2510_state *st = adap->dev->priv;
	const char *desc = adap->dev->desc->name;
	char *fe_name[] = {"", " LG TDQY-P001F", " SHARP:BS2F7HZ7395"};
	char *name = adap->fe->ops.info.name;

	strlcpy(name, desc, 128);
	strlcat(name, fe_name[st->tuner_config], 128);

	return 0;
}