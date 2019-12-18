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
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int adc_atten_t ;
typedef  int adc2_channel_t ;
struct TYPE_2__ {int sar_atten2; } ;

/* Variables and functions */
 int ADC2_CHANNEL_MAX ; 
 int ADC_ATTEN_11db ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_TIMEOUT ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ SENS ; 
 int /*<<< orphan*/  _lock_release (int /*<<< orphan*/ *) ; 
 int _lock_try_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adc2_pad_init (int) ; 
 int /*<<< orphan*/  adc2_spinlock ; 
 int /*<<< orphan*/  adc2_wifi_lock ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 

esp_err_t adc2_config_channel_atten(adc2_channel_t channel, adc_atten_t atten)
{
    RTC_MODULE_CHECK(channel < ADC2_CHANNEL_MAX, "ADC2 Channel Err", ESP_ERR_INVALID_ARG);
    RTC_MODULE_CHECK(atten <= ADC_ATTEN_11db, "ADC2 Atten Err", ESP_ERR_INVALID_ARG);

    adc2_pad_init(channel);
    portENTER_CRITICAL( &adc2_spinlock );

    //lazy initialization
    //avoid collision with other tasks
    if ( _lock_try_acquire( &adc2_wifi_lock ) == -1 ) {
        //try the lock, return if failed (wifi using).
        portEXIT_CRITICAL( &adc2_spinlock );
        return ESP_ERR_TIMEOUT;
    }
    SENS.sar_atten2 = ( SENS.sar_atten2 & ~(3<<(channel*2)) ) | ((atten&3) << (channel*2));
    _lock_release( &adc2_wifi_lock );

    portEXIT_CRITICAL( &adc2_spinlock );
    return ESP_OK;
}