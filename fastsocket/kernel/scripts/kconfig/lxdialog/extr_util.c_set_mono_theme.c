#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_60__   TYPE_9__ ;
typedef  struct TYPE_59__   TYPE_8__ ;
typedef  struct TYPE_58__   TYPE_7__ ;
typedef  struct TYPE_57__   TYPE_6__ ;
typedef  struct TYPE_56__   TYPE_5__ ;
typedef  struct TYPE_55__   TYPE_4__ ;
typedef  struct TYPE_54__   TYPE_3__ ;
typedef  struct TYPE_53__   TYPE_30__ ;
typedef  struct TYPE_52__   TYPE_2__ ;
typedef  struct TYPE_51__   TYPE_29__ ;
typedef  struct TYPE_50__   TYPE_28__ ;
typedef  struct TYPE_49__   TYPE_27__ ;
typedef  struct TYPE_48__   TYPE_26__ ;
typedef  struct TYPE_47__   TYPE_25__ ;
typedef  struct TYPE_46__   TYPE_24__ ;
typedef  struct TYPE_45__   TYPE_23__ ;
typedef  struct TYPE_44__   TYPE_22__ ;
typedef  struct TYPE_43__   TYPE_21__ ;
typedef  struct TYPE_42__   TYPE_20__ ;
typedef  struct TYPE_41__   TYPE_1__ ;
typedef  struct TYPE_40__   TYPE_19__ ;
typedef  struct TYPE_39__   TYPE_18__ ;
typedef  struct TYPE_38__   TYPE_17__ ;
typedef  struct TYPE_37__   TYPE_16__ ;
typedef  struct TYPE_36__   TYPE_15__ ;
typedef  struct TYPE_35__   TYPE_14__ ;
typedef  struct TYPE_34__   TYPE_13__ ;
typedef  struct TYPE_33__   TYPE_12__ ;
typedef  struct TYPE_32__   TYPE_11__ ;
typedef  struct TYPE_31__   TYPE_10__ ;

/* Type definitions */
struct TYPE_60__ {void* atr; } ;
struct TYPE_59__ {void* atr; } ;
struct TYPE_58__ {int /*<<< orphan*/  atr; } ;
struct TYPE_57__ {void* atr; } ;
struct TYPE_56__ {void* atr; } ;
struct TYPE_55__ {void* atr; } ;
struct TYPE_54__ {void* atr; } ;
struct TYPE_51__ {void* atr; } ;
struct TYPE_50__ {void* atr; } ;
struct TYPE_49__ {void* atr; } ;
struct TYPE_48__ {void* atr; } ;
struct TYPE_47__ {void* atr; } ;
struct TYPE_46__ {void* atr; } ;
struct TYPE_45__ {void* atr; } ;
struct TYPE_44__ {void* atr; } ;
struct TYPE_43__ {void* atr; } ;
struct TYPE_42__ {void* atr; } ;
struct TYPE_40__ {void* atr; } ;
struct TYPE_39__ {void* atr; } ;
struct TYPE_38__ {void* atr; } ;
struct TYPE_37__ {void* atr; } ;
struct TYPE_36__ {void* atr; } ;
struct TYPE_35__ {void* atr; } ;
struct TYPE_34__ {void* atr; } ;
struct TYPE_33__ {void* atr; } ;
struct TYPE_32__ {void* atr; } ;
struct TYPE_31__ {void* atr; } ;
struct TYPE_52__ {void* atr; } ;
struct TYPE_41__ {void* atr; } ;
struct TYPE_53__ {TYPE_29__ darrow; TYPE_28__ uarrow; TYPE_27__ check_selected; TYPE_26__ check; TYPE_25__ tag_key_selected; TYPE_24__ tag_key; TYPE_23__ tag_selected; TYPE_22__ tag; TYPE_21__ item_selected; TYPE_20__ item; TYPE_19__ menubox_border; TYPE_18__ menubox; TYPE_17__ position_indicator; TYPE_16__ searchbox_border; TYPE_15__ searchbox_title; TYPE_14__ searchbox; TYPE_13__ inputbox_border; TYPE_12__ inputbox; TYPE_11__ button_label_inactive; TYPE_10__ button_label_active; TYPE_9__ button_key_inactive; TYPE_8__ button_key_active; TYPE_7__ button_inactive; TYPE_6__ button_active; TYPE_5__ border; TYPE_4__ title; TYPE_3__ dialog; TYPE_2__ shadow; TYPE_1__ screen; } ;

/* Variables and functions */
 void* A_BOLD ; 
 int /*<<< orphan*/  A_DIM ; 
 void* A_NORMAL ; 
 void* A_REVERSE ; 
 TYPE_30__ dlg ; 

__attribute__((used)) static void set_mono_theme(void)
{
	dlg.screen.atr = A_NORMAL;
	dlg.shadow.atr = A_NORMAL;
	dlg.dialog.atr = A_NORMAL;
	dlg.title.atr = A_BOLD;
	dlg.border.atr = A_NORMAL;
	dlg.button_active.atr = A_REVERSE;
	dlg.button_inactive.atr = A_DIM;
	dlg.button_key_active.atr = A_REVERSE;
	dlg.button_key_inactive.atr = A_BOLD;
	dlg.button_label_active.atr = A_REVERSE;
	dlg.button_label_inactive.atr = A_NORMAL;
	dlg.inputbox.atr = A_NORMAL;
	dlg.inputbox_border.atr = A_NORMAL;
	dlg.searchbox.atr = A_NORMAL;
	dlg.searchbox_title.atr = A_BOLD;
	dlg.searchbox_border.atr = A_NORMAL;
	dlg.position_indicator.atr = A_BOLD;
	dlg.menubox.atr = A_NORMAL;
	dlg.menubox_border.atr = A_NORMAL;
	dlg.item.atr = A_NORMAL;
	dlg.item_selected.atr = A_REVERSE;
	dlg.tag.atr = A_BOLD;
	dlg.tag_selected.atr = A_REVERSE;
	dlg.tag_key.atr = A_BOLD;
	dlg.tag_key_selected.atr = A_REVERSE;
	dlg.check.atr = A_BOLD;
	dlg.check_selected.atr = A_REVERSE;
	dlg.uarrow.atr = A_BOLD;
	dlg.darrow.atr = A_BOLD;
}