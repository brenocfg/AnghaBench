#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* path; char* label; char* sublabel; char* rich_label; char* value; char* password_value; int path_enabled; int label_enabled; int rich_label_enabled; int value_enabled; int sublabel_enabled; scalar_t__ spacing; scalar_t__ type; scalar_t__ idx; scalar_t__ entry_idx; int /*<<< orphan*/  enum_idx; } ;
typedef  TYPE_1__ menu_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_UNKNOWN ; 

void menu_entry_init(menu_entry_t *entry)
{
   entry->path[0]            = '\0';
   entry->label[0]           = '\0';
   entry->sublabel[0]        = '\0';
   entry->rich_label[0]      = '\0';
   entry->value[0]           = '\0';
   entry->password_value[0]  = '\0';
   entry->enum_idx           = MSG_UNKNOWN;
   entry->entry_idx          = 0;
   entry->idx                = 0;
   entry->type               = 0;
   entry->spacing            = 0;
   entry->path_enabled       = true;
   entry->label_enabled      = true;
   entry->rich_label_enabled = true;
   entry->value_enabled      = true;
   entry->sublabel_enabled   = true;
}