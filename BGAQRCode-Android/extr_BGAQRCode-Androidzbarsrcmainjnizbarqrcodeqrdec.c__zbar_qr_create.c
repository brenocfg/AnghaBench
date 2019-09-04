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
typedef  int /*<<< orphan*/  qr_reader ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  qr_reader_init (int /*<<< orphan*/ *) ; 

qr_reader *_zbar_qr_create (void)
{
    qr_reader *reader = (qr_reader*)calloc(1, sizeof(*reader));
    qr_reader_init(reader);
    return(reader);
}