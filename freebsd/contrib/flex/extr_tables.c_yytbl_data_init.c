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
struct yytbl_data {int td_id; int /*<<< orphan*/  td_flags; } ;
typedef  enum yytbl_id { ____Placeholder_yytbl_id } yytbl_id ;

/* Variables and functions */
 int /*<<< orphan*/  YYTD_DATA32 ; 
 int /*<<< orphan*/  memset (struct yytbl_data*,int /*<<< orphan*/ ,int) ; 

int yytbl_data_init (struct yytbl_data *td, enum yytbl_id id)
{

	memset (td, 0, sizeof (struct yytbl_data));
	td->td_id = id;
	td->td_flags = YYTD_DATA32;
	return 0;
}