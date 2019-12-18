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
typedef  int wq_thactive_t ;
typedef  int /*<<< orphan*/  thread_qos_t ;

/* Variables and functions */
 int WQ_THACTIVE_BUCKET_WIDTH ; 
 int _wq_bucket (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline wq_thactive_t
_wq_thactive_offset_for_qos(thread_qos_t qos)
{
	return (wq_thactive_t)1 << (_wq_bucket(qos) * WQ_THACTIVE_BUCKET_WIDTH);
}