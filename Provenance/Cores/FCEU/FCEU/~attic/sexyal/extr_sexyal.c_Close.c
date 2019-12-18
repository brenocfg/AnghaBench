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
typedef  int /*<<< orphan*/  SexyAL_device ;

/* Variables and functions */
 int SexyALI_DSound_Close (int /*<<< orphan*/ *) ; 
 int SexyALI_OSS_Close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Close(SexyAL_device *device)
{
 #ifdef WIN32
 return(SexyALI_DSound_Close(device));
 #else
 return(SexyALI_OSS_Close(device));
 #endif
}