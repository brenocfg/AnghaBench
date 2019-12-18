#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ sbal; } ;
struct TYPE_7__ {scalar_t__ sbal; } ;
struct zfcp_qdio {TYPE_4__ req_q; TYPE_3__ resp_q; TYPE_1__* adapter; } ;
struct qdio_initialize {int no_input_qs; int no_output_qs; unsigned long int_parm; int flags; void** input_sbal_addr_array; void** output_sbal_addr_array; int /*<<< orphan*/  output_handler; int /*<<< orphan*/  input_handler; int /*<<< orphan*/  qdr_ac; int /*<<< orphan*/  qib_rflags; int /*<<< orphan*/  adapter_name; TYPE_2__* cdev; int /*<<< orphan*/  q_format; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_2__* ccw_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASCEBC (int /*<<< orphan*/ ,int) ; 
 int QDIO_INBOUND_0COPY_SBALS ; 
 int QDIO_OUTBOUND_0COPY_SBALS ; 
 int QDIO_USE_OUTBOUND_PCIS ; 
 int /*<<< orphan*/  QDIO_ZFCP_QFMT ; 
 int /*<<< orphan*/  QDR_AC_MULTI_BUFFER_ENABLE ; 
 int /*<<< orphan*/  QIB_RFLAGS_ENABLE_DATA_DIV ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ enable_multibuffer ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct qdio_initialize*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfcp_qdio_int_req ; 
 int /*<<< orphan*/  zfcp_qdio_int_resp ; 

__attribute__((used)) static void zfcp_qdio_setup_init_data(struct qdio_initialize *id,
				      struct zfcp_qdio *qdio)
{
	memset(id, 0, sizeof(*id));
	id->cdev = qdio->adapter->ccw_device;
	id->q_format = QDIO_ZFCP_QFMT;
	memcpy(id->adapter_name, dev_name(&id->cdev->dev), 8);
	ASCEBC(id->adapter_name, 8);
	id->qib_rflags = QIB_RFLAGS_ENABLE_DATA_DIV;
	if (enable_multibuffer)
		id->qdr_ac |= QDR_AC_MULTI_BUFFER_ENABLE;
	id->no_input_qs = 1;
	id->no_output_qs = 1;
	id->input_handler = zfcp_qdio_int_resp;
	id->output_handler = zfcp_qdio_int_req;
	id->int_parm = (unsigned long) qdio;
	id->flags = QDIO_INBOUND_0COPY_SBALS |
		    QDIO_OUTBOUND_0COPY_SBALS | QDIO_USE_OUTBOUND_PCIS;
	id->input_sbal_addr_array = (void **) (qdio->resp_q.sbal);
	id->output_sbal_addr_array = (void **) (qdio->req_q.sbal);
}