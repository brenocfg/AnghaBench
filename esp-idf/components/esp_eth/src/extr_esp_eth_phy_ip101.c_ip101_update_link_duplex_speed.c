#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ link_status; int /*<<< orphan*/  addr; TYPE_2__* eth; } ;
typedef  TYPE_1__ phy_ip101_t ;
typedef  scalar_t__ eth_speed_t ;
typedef  scalar_t__ eth_link_t ;
typedef  scalar_t__ eth_duplex_t ;
struct TYPE_13__ {scalar_t__ (* phy_reg_read ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* on_state_changed ) (TYPE_2__*,int /*<<< orphan*/ ,void*) ;} ;
typedef  TYPE_2__ esp_eth_mediator_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_14__ {int op_mode; int /*<<< orphan*/  val; } ;
typedef  TYPE_3__ cssr_reg_t ;
struct TYPE_15__ {scalar_t__ link_status; int /*<<< orphan*/  val; } ;
typedef  TYPE_4__ bmsr_reg_t ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ ETH_DUPLEX_FULL ; 
 scalar_t__ ETH_DUPLEX_HALF ; 
 scalar_t__ ETH_LINK_DOWN ; 
 scalar_t__ ETH_LINK_UP ; 
 int /*<<< orphan*/  ETH_PHY_BMSR_REG_ADDR ; 
 int /*<<< orphan*/  ETH_PHY_CSSR_REG_ADDR ; 
 scalar_t__ ETH_SPEED_100M ; 
 scalar_t__ ETH_SPEED_10M ; 
 int /*<<< orphan*/  ETH_STATE_DUPLEX ; 
 int /*<<< orphan*/  ETH_STATE_LINK ; 
 int /*<<< orphan*/  ETH_STATE_SPEED ; 
 int /*<<< orphan*/  PHY_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err ; 
 scalar_t__ ip101_page_select (TYPE_1__*,int) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub3 (TYPE_2__*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ stub4 (TYPE_2__*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ stub5 (TYPE_2__*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static esp_err_t ip101_update_link_duplex_speed(phy_ip101_t *ip101)
{
    esp_eth_mediator_t *eth = ip101->eth;
    eth_speed_t speed = ETH_SPEED_10M;
    eth_duplex_t duplex = ETH_DUPLEX_HALF;
    cssr_reg_t cssr;
    bmsr_reg_t bmsr;
    PHY_CHECK(ip101_page_select(ip101, 16) == ESP_OK, "select page 16 failed", err);
    PHY_CHECK(eth->phy_reg_read(eth, ip101->addr, ETH_PHY_BMSR_REG_ADDR, &(bmsr.val)) == ESP_OK,
              "read BMSR failed", err);
    eth_link_t link = bmsr.link_status ? ETH_LINK_UP : ETH_LINK_DOWN;
    /* check if link status changed */
    if (ip101->link_status != link) {
        /* when link up, read negotiation result */
        if (link == ETH_LINK_UP) {
            PHY_CHECK(eth->phy_reg_read(eth, ip101->addr, ETH_PHY_CSSR_REG_ADDR, &(cssr.val)) == ESP_OK,
                      "read CSSR failed", err);
            switch (cssr.op_mode) {
            case 1: //10M Half
                speed = ETH_SPEED_10M;
                duplex = ETH_DUPLEX_HALF;
                break;
            case 2: //100M Half
                speed = ETH_SPEED_100M;
                duplex = ETH_DUPLEX_HALF;
                break;
            case 5: //10M Full
                speed = ETH_SPEED_10M;
                duplex = ETH_DUPLEX_FULL;
                break;
            case 6: //100M Full
                speed = ETH_SPEED_100M;
                duplex = ETH_DUPLEX_FULL;
                break;
            default:
                break;
            }
            PHY_CHECK(eth->on_state_changed(eth, ETH_STATE_SPEED, (void *)speed) == ESP_OK,
                      "change speed failed", err);
            PHY_CHECK(eth->on_state_changed(eth, ETH_STATE_DUPLEX, (void *)duplex) == ESP_OK,
                      "change duplex failed", err);
        }
        PHY_CHECK(eth->on_state_changed(eth, ETH_STATE_LINK, (void *)link) == ESP_OK,
                  "chagne link failed", err);
        ip101->link_status = link;
    }
    return ESP_OK;
err:
    return ESP_FAIL;
}