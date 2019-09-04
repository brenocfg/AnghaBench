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
typedef  int /*<<< orphan*/ * qr_line ;

/* Variables and functions */
 scalar_t__ qr_line_eval (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void qr_line_orient(qr_line _l,int _x,int _y){
  if(qr_line_eval(_l,_x,_y)<0){
    _l[0]=-_l[0];
    _l[1]=-_l[1];
    _l[2]=-_l[2];
  }
}