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
typedef  int /*<<< orphan*/  VC_CONTAINER_READER_OPEN_FUNC_T ;

/* Variables and functions */
 int /*<<< orphan*/  DL_PREFIX_METADATA ; 
 int /*<<< orphan*/  load_library (void**,char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static VC_CONTAINER_READER_OPEN_FUNC_T load_metadata_reader(void **handle, const char *name)
{
   #define DL_PREFIX_METADATA "metadata_"
   return load_library(handle, name, DL_PREFIX_METADATA, 1);
}