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
typedef  int /*<<< orphan*/  WFC_STREAM_T ;
typedef  scalar_t__ VCOS_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_BLOCKPOOL_ALIGN_DEFAULT ; 
 int /*<<< orphan*/  VCOS_BLOCKPOOL_FLAG_NONE ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  WFC_LOG_LEVEL ; 
 int /*<<< orphan*/  WFC_STREAM_BLOCK_SIZE ; 
 int /*<<< orphan*/  WFC_STREAM_MAX_EXTENSIONS ; 
 int /*<<< orphan*/  log_cat ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 scalar_t__ vcos_blockpool_create_on_heap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ vcos_blockpool_extend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_register (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_log_set_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vcos_mutex_create (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wfc_stream_blockpool ; 
 int /*<<< orphan*/  wfc_stream_global_lock ; 

__attribute__((used)) static void wfc_stream_initialise(void)
{
   VCOS_STATUS_T status;

   vcos_log_set_level(&log_cat, WFC_LOG_LEVEL);
   vcos_log_register("wfc_client_stream", &log_cat);

   vcos_log_trace("%s", VCOS_FUNCTION);

   status = vcos_mutex_create(&wfc_stream_global_lock, "WFC stream global lock");
   vcos_assert(status == VCOS_SUCCESS);

   status = vcos_blockpool_create_on_heap(&wfc_stream_blockpool,
         WFC_STREAM_BLOCK_SIZE, sizeof(WFC_STREAM_T),
         VCOS_BLOCKPOOL_ALIGN_DEFAULT, VCOS_BLOCKPOOL_FLAG_NONE,
         "wfc stream pool");
   vcos_assert(status == VCOS_SUCCESS);

   status = vcos_blockpool_extend(&wfc_stream_blockpool,
         WFC_STREAM_MAX_EXTENSIONS, WFC_STREAM_BLOCK_SIZE);
   vcos_assert(status == VCOS_SUCCESS);
}