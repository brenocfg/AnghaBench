void m68k_unused_16_w(unsigned int address, unsigned int data)
{
#ifdef LOGERROR
  error("Unused write16 %08X = %04X (%08X)\n", address, data, m68k_get_reg(M68K_REG_PC));
#endif
}