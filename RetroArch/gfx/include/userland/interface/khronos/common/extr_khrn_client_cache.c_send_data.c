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
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int CLIENT_MAKE_CURRENT_SIZE ; 
 int /*<<< orphan*/  GLINTCACHEDATA_ID ; 
 int MERGE_BUFFER_SIZE ; 
 int /*<<< orphan*/  RPC_CALL3_IN_CTRL (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  RPC_SIZEI (int) ; 
 int /*<<< orphan*/  RPC_UINT (int) ; 
 int _min (int,int) ; 
 int /*<<< orphan*/  glintCacheData_impl ; 

__attribute__((used)) static void send_data(CLIENT_THREAD_STATE_T *thread, int base, const void *data, int len)
{
   int off = 0;

   while (len > 0) {
      int chunk = _min(len, MERGE_BUFFER_SIZE-CLIENT_MAKE_CURRENT_SIZE-12-8);

      RPC_CALL3_IN_CTRL(glintCacheData_impl,
                        thread,
                        GLINTCACHEDATA_ID,
                        RPC_UINT(base + off),
                        RPC_SIZEI(chunk),
                        (char *)data + off,
                        chunk);

      off += chunk;
      len -= chunk;
   }
}