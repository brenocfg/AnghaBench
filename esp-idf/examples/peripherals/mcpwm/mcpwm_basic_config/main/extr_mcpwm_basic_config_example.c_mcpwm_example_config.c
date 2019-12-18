#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int frequency; double cmpr_a; double cmpr_b; void* duty_mode; void* counter_mode; } ;
typedef  TYPE_2__ mcpwm_config_t ;
struct TYPE_9__ {int carrier_period; int carrier_duty; int pulse_width_in_os; int /*<<< orphan*/  carrier_ivt_mode; int /*<<< orphan*/  carrier_os_mode; } ;
typedef  TYPE_3__ mcpwm_carrier_config_t ;
struct TYPE_7__ {int val; } ;
struct TYPE_10__ {TYPE_1__ int_ena; } ;

/* Variables and functions */
 int CAP0_INT_EN ; 
 int CAP1_INT_EN ; 
 int CAP2_INT_EN ; 
 int /*<<< orphan*/  ESP_INTR_FLAG_IRAM ; 
 TYPE_6__** MCPWM ; 
 int /*<<< orphan*/  MCPWM_ACTIVE_RED_FED_FROM_PWMXA ; 
 int /*<<< orphan*/  MCPWM_BYPASS_FED ; 
 int /*<<< orphan*/  MCPWM_BYPASS_RED ; 
 int /*<<< orphan*/  MCPWM_CARRIER_OUT_IVT_EN ; 
 void* MCPWM_DUTY_MODE_0 ; 
 void* MCPWM_DUTY_MODE_1 ; 
 int /*<<< orphan*/  MCPWM_FORCE_MCPWMXA_HIGH ; 
 int /*<<< orphan*/  MCPWM_FORCE_MCPWMXA_LOW ; 
 int /*<<< orphan*/  MCPWM_FORCE_MCPWMXB_HIGH ; 
 int /*<<< orphan*/  MCPWM_FORCE_MCPWMXB_LOW ; 
 int /*<<< orphan*/  MCPWM_HIGH_LEVEL_TGR ; 
 int /*<<< orphan*/  MCPWM_ONESHOT_MODE_EN ; 
 int /*<<< orphan*/  MCPWM_POS_EDGE ; 
 int /*<<< orphan*/  MCPWM_SELECT_CAP0 ; 
 int /*<<< orphan*/  MCPWM_SELECT_CAP1 ; 
 int /*<<< orphan*/  MCPWM_SELECT_CAP2 ; 
 int /*<<< orphan*/  MCPWM_SELECT_F0 ; 
 int /*<<< orphan*/  MCPWM_SELECT_F1 ; 
 int /*<<< orphan*/  MCPWM_SELECT_F2 ; 
 int /*<<< orphan*/  MCPWM_SELECT_SYNC0 ; 
 int /*<<< orphan*/  MCPWM_TIMER_0 ; 
 int /*<<< orphan*/  MCPWM_TIMER_1 ; 
 int /*<<< orphan*/  MCPWM_TIMER_2 ; 
 size_t MCPWM_UNIT_0 ; 
 void* MCPWM_UP_COUNTER ; 
 void* MCPWM_UP_DOWN_COUNTER ; 
 int /*<<< orphan*/  isr_handler ; 
 int /*<<< orphan*/  mcpwm_capture_enable (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_carrier_init (size_t,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  mcpwm_deadtime_enable (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mcpwm_example_gpio_initialize () ; 
 int /*<<< orphan*/  mcpwm_fault_init (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_fault_set_oneshot_mode (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_init (size_t,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  mcpwm_isr_register (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcpwm_sync_enable (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mcpwm_example_config(void *arg)
{
    //1. mcpwm gpio initialization
    mcpwm_example_gpio_initialize();

    //2. initialize mcpwm configuration
    printf("Configuring Initial Parameters of mcpwm...\n");
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 1000;    //frequency = 1000Hz
    pwm_config.cmpr_a = 60.0;       //duty cycle of PWMxA = 60.0%
    pwm_config.cmpr_b = 50.0;       //duty cycle of PWMxb = 50.0%
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);   //Configure PWM0A & PWM0B with above settings
    pwm_config.frequency = 500;     //frequency = 500Hz
    pwm_config.cmpr_a = 45.9;       //duty cycle of PWMxA = 45.9%
    pwm_config.cmpr_b = 7.0;    //duty cycle of PWMxb = 07.0%
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);   //Configure PWM1A & PWM1B with above settings
    pwm_config.frequency = 400;     //frequency = 400Hz
    pwm_config.cmpr_a = 23.2;       //duty cycle of PWMxA = 23.2%
    pwm_config.cmpr_b = 97.0;       //duty cycle of PWMxb = 97.0%
    pwm_config.counter_mode = MCPWM_UP_DOWN_COUNTER; //frequency is half when up down count mode is set i.e. SYMMETRIC PWM
    pwm_config.duty_mode = MCPWM_DUTY_MODE_1;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_2, &pwm_config);   //Configure PWM2A & PWM2B with above settings

#if MCPWM_EN_CARRIER
    //3. carrier configuration
    //comment if you don't want to use carrier mode
    //in carrier mode very high frequency carrier signal is generated at mcpwm high level signal
    mcpwm_carrier_config_t chop_config;
    chop_config.carrier_period = 6;         //carrier period = (6 + 1)*800ns
    chop_config.carrier_duty = 3;           //carrier duty = (3)*12.5%
    chop_config.carrier_os_mode = MCPWM_ONESHOT_MODE_EN; //If one shot mode is enabled then set pulse width, if disabled no need to set pulse width
    chop_config.pulse_width_in_os = 3;      //first pulse width = (3 + 1)*carrier_period
    chop_config.carrier_ivt_mode = MCPWM_CARRIER_OUT_IVT_EN; //output signal inversion enable
    mcpwm_carrier_init(MCPWM_UNIT_0, MCPWM_TIMER_2, &chop_config);  //Enable carrier on PWM2A and PWM2B with above settings
    //use mcpwm_carrier_disable function to disable carrier on mcpwm timer on which it was enabled
#endif

#if MCPWM_EN_DEADTIME
    //4. deadtime configuration
    //comment if you don't want to use deadtime submodule
    //add rising edge delay or falling edge delay. There are 8 different types, each explained in mcpwm_deadtime_type_t in mcpwm.h
    mcpwm_deadtime_enable(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_BYPASS_FED, 1000, 1000);   //Enable deadtime on PWM2A and PWM2B with red = (1000)*100ns on PWM2A
    mcpwm_deadtime_enable(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_BYPASS_RED, 300, 2000);        //Enable deadtime on PWM1A and PWM1B with fed = (2000)*100ns on PWM1B
    mcpwm_deadtime_enable(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_ACTIVE_RED_FED_FROM_PWMXA, 656, 67);  //Enable deadtime on PWM0A and PWM0B with red = (656)*100ns & fed = (67)*100ns on PWM0A and PWM0B generated from PWM0A
    //use mcpwm_deadtime_disable function to disable deadtime on mcpwm timer on which it was enabled
#endif

#if MCPWM_EN_FAULT
    //5. enable fault condition
    //comment if you don't want to use fault submodule, also u can comment the fault gpio signals
    //whenever fault occurs you can configure mcpwm signal to either force low, force high or toggle.
    //in cycmode, as soon as fault condition is over, the mcpwm signal is resumed, whereas in oneshot mode you need to reset.
    mcpwm_fault_init(MCPWM_UNIT_0, MCPWM_HIGH_LEVEL_TGR, MCPWM_SELECT_F0); //Enable FAULT, when high level occurs on FAULT0 signal
    mcpwm_fault_init(MCPWM_UNIT_0, MCPWM_HIGH_LEVEL_TGR, MCPWM_SELECT_F1); //Enable FAULT, when high level occurs on FAULT1 signal
    mcpwm_fault_init(MCPWM_UNIT_0, MCPWM_HIGH_LEVEL_TGR, MCPWM_SELECT_F2); //Enable FAULT, when high level occurs on FAULT2 signal
    mcpwm_fault_set_oneshot_mode(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_SELECT_F0, MCPWM_FORCE_MCPWMXA_HIGH, MCPWM_FORCE_MCPWMXB_LOW); //Action taken on PWM1A and PWM1B, when FAULT0 occurs
    mcpwm_fault_set_oneshot_mode(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_SELECT_F1, MCPWM_FORCE_MCPWMXA_LOW, MCPWM_FORCE_MCPWMXB_HIGH); //Action taken on PWM1A and PWM1B, when FAULT1 occurs
    mcpwm_fault_set_oneshot_mode(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_SELECT_F2, MCPWM_FORCE_MCPWMXA_HIGH, MCPWM_FORCE_MCPWMXB_LOW); //Action taken on PWM0A and PWM0B, when FAULT2 occurs
    mcpwm_fault_set_oneshot_mode(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_SELECT_F1, MCPWM_FORCE_MCPWMXA_LOW, MCPWM_FORCE_MCPWMXB_HIGH); //Action taken on PWM0A and PWM0B, when FAULT1 occurs
#endif

#if MCPWM_EN_SYNC
    //6. Syncronization configuration
    //comment if you don't want to use sync submodule, also u can comment the sync gpio signals
    //here synchronization occurs on PWM1A and PWM1B
    mcpwm_sync_enable(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_SELECT_SYNC0, 200);    //Load counter value with 20% of period counter of mcpwm timer 1 when sync 0 occurs
#endif

#if MCPWM_EN_CAPTURE
    //7. Capture configuration
    //comment if you don't want to use capture submodule, also u can comment the capture gpio signals
    //configure CAP0, CAP1 and CAP2 signal to start capture counter on rising edge
    //we generate a gpio_test_signal of 20ms on GPIO 12 and connect it to one of the capture signal, the disp_captured_function displays the time between rising edge
    //In general practice you can connect Capture  to external signal, measure time between rising edge or falling edge and take action accordingly
    mcpwm_capture_enable(MCPWM_UNIT_0, MCPWM_SELECT_CAP0, MCPWM_POS_EDGE, 0);  //capture signal on rising edge, prescale = 0 i.e. 800,000,000 counts is equal to one second
    mcpwm_capture_enable(MCPWM_UNIT_0, MCPWM_SELECT_CAP2, MCPWM_POS_EDGE, 0);  //capture signal on rising edge, prescale = 0 i.e. 800,000,000 counts is equal to one second
    mcpwm_capture_enable(MCPWM_UNIT_0, MCPWM_SELECT_CAP1, MCPWM_POS_EDGE, 0);  //capture signal on rising edge, prescale = 0 i.e. 800,000,000 counts is equal to one second
    //enable interrupt, so each this a rising edge occurs interrupt is triggered
    MCPWM[MCPWM_UNIT_0]->int_ena.val = CAP0_INT_EN | CAP1_INT_EN | CAP2_INT_EN;  //Enable interrupt on  CAP0, CAP1 and CAP2 signal
    mcpwm_isr_register(MCPWM_UNIT_0, isr_handler, NULL, ESP_INTR_FLAG_IRAM, NULL);  //Set ISR Handler
#endif
    vTaskDelete(NULL);
}