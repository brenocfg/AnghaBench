#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int SR; } ;

/* Variables and functions */
 int SPI_SR_BSY ; 
 int SPI_SR_TXE ; 
 TYPE_1__* TLC59401_SPI ; 

__attribute__((used)) static bool isIdle() {
    if(TLC59401_SPI->SR & SPI_SR_BSY)
        return false;
    if(((TLC59401_SPI->SR & SPI_SR_TXE) == 0))
        return false;
    return true;
}