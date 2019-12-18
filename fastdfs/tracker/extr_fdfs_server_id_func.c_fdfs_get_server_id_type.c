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

/* Variables and functions */
 int FDFS_ID_TYPE_IP_ADDRESS ; 
 int FDFS_ID_TYPE_SERVER_ID ; 
 int const FDFS_MAX_SERVER_ID ; 

int  fdfs_get_server_id_type(const int id)
{
  if (id > 0 && id <= FDFS_MAX_SERVER_ID)
  {
    return FDFS_ID_TYPE_SERVER_ID;
  }
  else
  {
    return FDFS_ID_TYPE_IP_ADDRESS;
  }
}