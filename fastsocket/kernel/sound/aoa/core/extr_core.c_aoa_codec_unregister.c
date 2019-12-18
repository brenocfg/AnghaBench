#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct aoa_codec {int /*<<< orphan*/  owner; int /*<<< orphan*/ * fabric; int /*<<< orphan*/  (* exit ) (struct aoa_codec*) ;int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* remove_codec ) (struct aoa_codec*) ;} ;

/* Variables and functions */
 TYPE_1__* fabric ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct aoa_codec*) ; 
 int /*<<< orphan*/  stub2 (struct aoa_codec*) ; 

void aoa_codec_unregister(struct aoa_codec *codec)
{
	list_del(&codec->list);
	if (codec->fabric && codec->exit)
		codec->exit(codec);
	if (fabric && fabric->remove_codec)
		fabric->remove_codec(codec);
	codec->fabric = NULL;
	module_put(codec->owner);
}