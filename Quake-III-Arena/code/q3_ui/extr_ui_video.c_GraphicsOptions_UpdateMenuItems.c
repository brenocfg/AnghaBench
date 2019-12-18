#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_16__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_32__ {int curvalue; } ;
struct TYPE_25__ {int /*<<< orphan*/  flags; } ;
struct TYPE_31__ {int curvalue; TYPE_2__ generic; } ;
struct TYPE_30__ {scalar_t__ curvalue; } ;
struct TYPE_29__ {scalar_t__ curvalue; } ;
struct TYPE_28__ {scalar_t__ curvalue; } ;
struct TYPE_24__ {int /*<<< orphan*/  flags; } ;
struct TYPE_27__ {int curvalue; TYPE_1__ generic; } ;
struct TYPE_26__ {scalar_t__ curvalue; } ;
struct TYPE_20__ {int flags; } ;
struct TYPE_21__ {TYPE_13__ generic; } ;
struct TYPE_19__ {scalar_t__ curvalue; } ;
struct TYPE_18__ {scalar_t__ curvalue; } ;
struct TYPE_17__ {int curvalue; } ;
struct TYPE_23__ {TYPE_14__ apply; TYPE_12__ filter; TYPE_11__ geometry; TYPE_10__ texturebits; TYPE_9__ driver; TYPE_8__ colordepth; TYPE_7__ lighting; TYPE_6__ tq; TYPE_5__ allow_extensions; TYPE_4__ fs; TYPE_3__ mode; } ;
struct TYPE_22__ {scalar_t__ mode; int fullscreen; scalar_t__ extensions; scalar_t__ tq; scalar_t__ lighting; int colordepth; int driver; int texturebits; scalar_t__ geometry; scalar_t__ filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  GraphicsOptions_CheckConfig () ; 
 int /*<<< orphan*/  QMF_GRAYED ; 
 int QMF_HIDDEN ; 
 int QMF_INACTIVE ; 
 TYPE_16__ s_graphicsoptions ; 
 TYPE_15__ s_ivo ; 

__attribute__((used)) static void GraphicsOptions_UpdateMenuItems( void )
{
	if ( s_graphicsoptions.driver.curvalue == 1 )
	{
		s_graphicsoptions.fs.curvalue = 1;
		s_graphicsoptions.fs.generic.flags |= QMF_GRAYED;
		s_graphicsoptions.colordepth.curvalue = 1;
	}
	else
	{
		s_graphicsoptions.fs.generic.flags &= ~QMF_GRAYED;
	}

	if ( s_graphicsoptions.fs.curvalue == 0 || s_graphicsoptions.driver.curvalue == 1 )
	{
		s_graphicsoptions.colordepth.curvalue = 0;
		s_graphicsoptions.colordepth.generic.flags |= QMF_GRAYED;
	}
	else
	{
		s_graphicsoptions.colordepth.generic.flags &= ~QMF_GRAYED;
	}

	if ( s_graphicsoptions.allow_extensions.curvalue == 0 )
	{
		if ( s_graphicsoptions.texturebits.curvalue == 0 )
		{
			s_graphicsoptions.texturebits.curvalue = 1;
		}
	}

	s_graphicsoptions.apply.generic.flags |= QMF_HIDDEN|QMF_INACTIVE;

	if ( s_ivo.mode != s_graphicsoptions.mode.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.fullscreen != s_graphicsoptions.fs.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.extensions != s_graphicsoptions.allow_extensions.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.tq != s_graphicsoptions.tq.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.lighting != s_graphicsoptions.lighting.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.colordepth != s_graphicsoptions.colordepth.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.driver != s_graphicsoptions.driver.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.texturebits != s_graphicsoptions.texturebits.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.geometry != s_graphicsoptions.geometry.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}
	if ( s_ivo.filter != s_graphicsoptions.filter.curvalue )
	{
		s_graphicsoptions.apply.generic.flags &= ~(QMF_HIDDEN|QMF_INACTIVE);
	}

	GraphicsOptions_CheckConfig();
}