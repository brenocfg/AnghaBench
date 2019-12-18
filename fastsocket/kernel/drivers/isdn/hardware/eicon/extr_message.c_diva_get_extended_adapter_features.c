#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  features ;
struct TYPE_14__ {int /*<<< orphan*/  (* request ) (TYPE_4__*) ;scalar_t__ Id; } ;
struct TYPE_13__ {scalar_t__* user; } ;
struct TYPE_10__ {int buffer_length_in_bytes; char* features; } ;
struct TYPE_11__ {TYPE_1__ info; int /*<<< orphan*/  Rc; scalar_t__ Req; } ;
struct TYPE_12__ {TYPE_2__ xdi_extended_features; } ;
typedef  TYPE_3__ IDI_SYNC_REQ ;
typedef  TYPE_4__ ENTITY ;
typedef  TYPE_5__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 int DIVA_CAPI_USE_CMA ; 
 int DIVA_CAPI_XDI_PROVIDES_NO_CANCEL ; 
 int DIVA_CAPI_XDI_PROVIDES_RX_DMA ; 
 int DIVA_CAPI_XDI_PROVIDES_SDRAM_BAR ; 
 char DIVA_XDI_EXTENDED_FEATURES_VALID ; 
 char DIVA_XDI_EXTENDED_FEATURE_CMA ; 
 char DIVA_XDI_EXTENDED_FEATURE_NO_CANCEL_RC ; 
 char DIVA_XDI_EXTENDED_FEATURE_RX_DMA ; 
 char DIVA_XDI_EXTENDED_FEATURE_SDRAM_BAR ; 
 int /*<<< orphan*/  IDI_SYNC_REQ_XDI_GET_EXTENDED_FEATURES ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diva_ask_for_xdi_sdram_bar (TYPE_5__*,TYPE_3__*) ; 
 int diva_xdi_extended_features ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static void diva_get_extended_adapter_features (DIVA_CAPI_ADAPTER  * a) {
  IDI_SYNC_REQ   * preq;
    char buffer[              ((sizeof(preq->xdi_extended_features)+4) > sizeof(ENTITY)) ?                     (sizeof(preq->xdi_extended_features)+4) : sizeof(ENTITY)];

    char features[4];
  preq = (IDI_SYNC_REQ   *)&buffer[0];

  if (!diva_xdi_extended_features) {
    ENTITY   * e = (ENTITY   *)preq;
    diva_xdi_extended_features |= 0x80000000;

    e->user[0] = a->Id - 1;
    preq->xdi_extended_features.Req = 0;
    preq->xdi_extended_features.Rc  = IDI_SYNC_REQ_XDI_GET_EXTENDED_FEATURES;
    preq->xdi_extended_features.info.buffer_length_in_bytes = sizeof(features);
    preq->xdi_extended_features.info.features = &features[0];

    (*(a->request))(e);

    if (features[0] & DIVA_XDI_EXTENDED_FEATURES_VALID) {
      /*
         Check features located in the byte '0'
         */
      if (features[0] & DIVA_XDI_EXTENDED_FEATURE_CMA) {
        diva_xdi_extended_features |= DIVA_CAPI_USE_CMA;
      }
      if (features[0] & DIVA_XDI_EXTENDED_FEATURE_RX_DMA) {
        diva_xdi_extended_features |= DIVA_CAPI_XDI_PROVIDES_RX_DMA;
        dbug(1,dprintf("XDI provides RxDMA"));
      }
      if (features[0] & DIVA_XDI_EXTENDED_FEATURE_SDRAM_BAR) {
        diva_xdi_extended_features |= DIVA_CAPI_XDI_PROVIDES_SDRAM_BAR;
      }
      if (features[0] & DIVA_XDI_EXTENDED_FEATURE_NO_CANCEL_RC) {
        diva_xdi_extended_features |= DIVA_CAPI_XDI_PROVIDES_NO_CANCEL;
        dbug(3,dprintf("XDI provides NO_CANCEL_RC feature"));
      }

    }
  }

  diva_ask_for_xdi_sdram_bar (a, preq);
}