#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  (* request ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  channels; int /*<<< orphan*/  features; int /*<<< orphan*/  type; } ;
struct TYPE_12__ {TYPE_2__ d; } ;
typedef  TYPE_4__ diva_um_idi_adapter_t ;
struct TYPE_13__ {scalar_t__ serial_number; int /*<<< orphan*/  name; int /*<<< orphan*/  channels; int /*<<< orphan*/  features; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ diva_um_idi_adapter_features_t ;
struct TYPE_11__ {scalar_t__ serial; int /*<<< orphan*/  Rc; scalar_t__ Req; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; int /*<<< orphan*/  Rc; scalar_t__ Req; } ;
struct TYPE_14__ {TYPE_3__ GetSerial; TYPE_1__ GetName; } ;
typedef  TYPE_6__ IDI_SYNC_REQ ;
typedef  int /*<<< orphan*/  ENTITY ;

/* Variables and functions */
 int /*<<< orphan*/  IDI_SYNC_REQ_GET_NAME ; 
 int /*<<< orphan*/  IDI_SYNC_REQ_GET_SERIAL ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
diva_user_mode_idi_adapter_features(diva_um_idi_adapter_t * a,
				    diva_um_idi_adapter_features_t *
				    features)
{
	IDI_SYNC_REQ sync_req;

	if ((a) && (a->d.request)) {
		features->type = a->d.type;
		features->features = a->d.features;
		features->channels = a->d.channels;
		memset(features->name, 0, sizeof(features->name));

		sync_req.GetName.Req = 0;
		sync_req.GetName.Rc = IDI_SYNC_REQ_GET_NAME;
		(*(a->d.request)) ((ENTITY *) & sync_req);
		strlcpy(features->name, sync_req.GetName.name,
			sizeof(features->name));

		sync_req.GetSerial.Req = 0;
		sync_req.GetSerial.Rc = IDI_SYNC_REQ_GET_SERIAL;
		sync_req.GetSerial.serial = 0;
		(*(a->d.request)) ((ENTITY *) & sync_req);
		features->serial_number = sync_req.GetSerial.serial;
	}

	return ((a) ? 0 : -1);
}