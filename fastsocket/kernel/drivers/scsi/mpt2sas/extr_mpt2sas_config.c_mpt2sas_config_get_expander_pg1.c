#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct MPT2SAS_ADAPTER {int dummy; } ;
struct TYPE_5__ {int PageNumber; int /*<<< orphan*/  PageVersion; int /*<<< orphan*/  PageType; } ;
struct TYPE_6__ {int /*<<< orphan*/  Action; int /*<<< orphan*/  PageAddress; int /*<<< orphan*/  PageBufferSGE; TYPE_1__ Header; int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  Function; } ;
typedef  int /*<<< orphan*/  Mpi2ExpanderPage1_t ;
typedef  TYPE_2__ Mpi2ConfigRequest_t ;
typedef  int /*<<< orphan*/  Mpi2ConfigReply_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPI2_CONFIG_ACTION_PAGE_HEADER ; 
 int /*<<< orphan*/  MPI2_CONFIG_ACTION_PAGE_READ_CURRENT ; 
 int /*<<< orphan*/  MPI2_CONFIG_EXTPAGETYPE_SAS_EXPANDER ; 
 int /*<<< orphan*/  MPI2_CONFIG_PAGETYPE_EXTENDED ; 
 int /*<<< orphan*/  MPI2_FUNCTION_CONFIG ; 
 int /*<<< orphan*/  MPI2_SASEXPANDER1_PAGEVERSION ; 
 int MPI2_SAS_EXPAND_PGAD_FORM_HNDL_PHY_NUM ; 
 int MPI2_SAS_EXPAND_PGAD_PHYNUM_SHIFT ; 
 int /*<<< orphan*/  MPT2_CONFIG_PAGE_DEFAULT_TIMEOUT ; 
 int _config_request (struct MPT2SAS_ADAPTER*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpt2sas_base_build_zero_len_sge (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ *) ; 

int
mpt2sas_config_get_expander_pg1(struct MPT2SAS_ADAPTER *ioc, Mpi2ConfigReply_t
    *mpi_reply, Mpi2ExpanderPage1_t *config_page, u32 phy_number,
    u16 handle)
{
	Mpi2ConfigRequest_t mpi_request;
	int r;

	memset(&mpi_request, 0, sizeof(Mpi2ConfigRequest_t));
	mpi_request.Function = MPI2_FUNCTION_CONFIG;
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	mpi_request.Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	mpi_request.ExtPageType = MPI2_CONFIG_EXTPAGETYPE_SAS_EXPANDER;
	mpi_request.Header.PageNumber = 1;
	mpi_request.Header.PageVersion = MPI2_SASEXPANDER1_PAGEVERSION;
	mpt2sas_base_build_zero_len_sge(ioc, &mpi_request.PageBufferSGE);
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT2_CONFIG_PAGE_DEFAULT_TIMEOUT, NULL, 0);
	if (r)
		goto out;

	mpi_request.PageAddress =
	    cpu_to_le32(MPI2_SAS_EXPAND_PGAD_FORM_HNDL_PHY_NUM |
	    (phy_number << MPI2_SAS_EXPAND_PGAD_PHYNUM_SHIFT) | handle);
	mpi_request.Action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	r = _config_request(ioc, &mpi_request, mpi_reply,
	    MPT2_CONFIG_PAGE_DEFAULT_TIMEOUT, config_page,
	    sizeof(*config_page));
 out:
	return r;
}