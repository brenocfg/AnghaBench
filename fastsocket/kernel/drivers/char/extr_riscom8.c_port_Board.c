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
struct riscom_port {int dummy; } ;
struct riscom_board {int dummy; } ;

/* Variables and functions */
 size_t RC_BOARD (struct riscom_port const*) ; 
 struct riscom_board* rc_board ; 
 int rc_port ; 

__attribute__((used)) static inline struct riscom_board *port_Board(struct riscom_port const *port)
{
	return &rc_board[RC_BOARD(port - rc_port)];
}